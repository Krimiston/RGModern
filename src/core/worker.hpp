// Copyright (c) 2022 Xiaomi Guo
// Modern Ruby Game Engine (RGM) is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan
// PSL v2. You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the
// Mulan PSL v2 for more details.

#pragma once
#include "datalist.hpp"
#include "kernel_active.hpp"
#include "scheduler.hpp"
#include "semaphore.hpp"
#include "tasklist.hpp"
#include "type_traits.hpp"

namespace rgm::core {
/**
 * @brief worker 类用于执行一系列的任务。
 *
 * @tparam T_kernel 任务执行的逻辑，分为主动模式和被动模式。
 * @tparam Args 可以执行的任务列表。
 */
template <template <typename> class T_kernel, typename... Args>
struct worker {
  using T_tasklist = tasklist<Args...>;
  using T_tasks = T_tasklist::tasks;
  using T_kernel_tasks = traits::remove_dummy_t<T_tasks, worker>;
  using T_datalist = typename T_tasklist::data::to<datalist>;

  /** 保存父类的指针地址用于向下转型为 scheduler<> 的派生类指针 */
  scheduler<>* p_scheduler;
  /** datalist 类，存储的变量可供所有的任务读写 */
  T_datalist* p_data;
  /**
   * @brief 任务执行的逻辑
   * @tparam T_kernel_tasks 包含了所有可以执行的任务的 TypeList
   */
  T_kernel<T_kernel_tasks> m_kernel;

  /**
   * @brief 根据不同的变量类型，获取相应的共享变量。
   *
   * @tparam T 变量类型
   * @return auto& 返回 T 类型变量的引用
   */
  template <typename T>
  auto& get() {
    return p_data->template get<T>();
  }

  /**
   * @brief worker 主要执行的内容，会在单独的线程里执行。
   * @note 按照以下顺序执行：
   * 1. 创建 datalist
   * 2. 按顺序执行任务列表的静态 before 函数
   * 3. 执行 kernel 的 run 函数
   * 4. 设置 running = false
   * 5. 按倒序执行任务列表的静态 after 函数
   * 6. 析构 datalist
   */
  void run() {
    if constexpr (config::output_level > 0) {
      int size = sizeof(typename T_kernel<T_kernel_tasks>::T_variants);
      printf("blocksize = %d\n", size);
    }

    T_datalist data;
    this->p_data = &data;

    traits::for_each<T_tasks>::before(*this);

    m_kernel.run(*this);
    if (p_scheduler->running) p_scheduler->running = false;

    traits::for_each<T_tasks>::after(*this);
  }

  /** 获取 worker 的运行状况 */
  bool running() { return p_scheduler->running; }

  /**
   * @brief 广播任务，可能会被某个 worker 接受。
   *
   * @tparam T 被广播的任务类型。
   * @tparam U 辅助 scheduler<>* 向下转型，延迟到 magic_cast 的特化之后。
   * @param task 被广播的任务，必须是右值，表示该任务已经离开作用域。
   * @return true 某个 worker 接受了该任务。
   * @return false 没有任何 worker 接受了该任务。
   */
  template <typename T, typename U = scheduler<>*>
  bool send(T&& task) {
    using base_t = U;
    using derived_t = traits::magic_cast<U>::type;

    static_assert(std::is_rvalue_reference_v<T&&>,
                  "Task must be passed as R-value!");
    static_assert(!std::same_as<base_t, derived_t>,
                  "Failed to downcast scheduler<>* !");

    return static_cast<derived_t>(p_scheduler)
        ->template broadcast(std::move(task));
  }

  // 向其他线程发送 T 指令，阻塞线程直到 T 指令异步执行完毕。
  template <typename T_cmd>
  void wait() {
    m_kernel.m_pause.acquire([this]() { send(T_cmd{&(m_kernel.m_pause)}); });
  }

  /** 只有 kernel 为主动模式才生效，清空当前管道内积压的全部任务。 */
  void step() {
    static_assert(std::is_base_of_v<kernel_active<T_kernel_tasks>,
                                    T_kernel<T_kernel_tasks>>);

    m_kernel.step(*this);
  }

  /** send 的别名 */
  template <typename T>
  void operator<<(T&& task) {
    send(std::forward<T>(task));
  }
};
}  // namespace rgm::core
