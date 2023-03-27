// zlib License

// Copyright (C) [2023] [Xiaomi Guo]

// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.

// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once
#include "core/core.hpp"
#include "detail.hpp"
#include "ruby.hpp"
#include "timer.hpp"

namespace rgm::base {

/** @brief 任务：使 ruby 线程抛出 Interrupt 异常 */
struct interrupt_signal {
  void run(auto&) {
    rb_raise(rb_eInterrupt, "Interrupted by another thread.\n");
  }
};

/** @brief 创建 synchronize 相关的 ruby 方法 */
struct init_synchronize {
  using data = std::tuple<timer>;

  static void before(auto& this_worker) {
    static decltype(auto) worker = this_worker;

    /** wrapper 类，创建静态方法供 ruby 的模块绑定 */
    struct wrapper {
      /** RGM::Base.synchronize 方法 */
      static VALUE synchronize(VALUE, VALUE thread_id_) {
        Check_Type(thread_id_, T_FIXNUM);
        int thread_id = FIX2INT(thread_id_);

        if (thread_id & 0b0001) RGMWAIT(1);
        if (thread_id & 0b0010) RGMWAIT(2);
        if (thread_id & 0b0100) RGMWAIT(3);
        if (thread_id & 0b1000) RGMWAIT(4);

        RGMDATA(timer).reset();
        return Qnil;
      }

      static VALUE check_delay(VALUE, VALUE frame_rate_) {
        double freq = 1.0 / detail::from_ruby<double>(frame_rate_);
        RGMDATA(timer).tick(freq);
        return Qnil;
      }
    };

    VALUE rb_mRGM = rb_define_module("RGM");
    VALUE rb_mRGM_Base = rb_define_module_under(rb_mRGM, "Base");
    rb_define_module_function(rb_mRGM_Base, "synchronize", wrapper::synchronize,
                              1);
    rb_define_module_function(rb_mRGM_Base, "check_delay", wrapper::check_delay,
                              1);
    RGMDATA(timer).reset();
  }
};
}  // namespace rgm::base