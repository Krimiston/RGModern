// zlib License
//
// copyright (C) 2023 Guoxiaomi and Krimiston
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once
#include "ext/ext.hpp"
#include "rmxp/rmxp.hpp"

namespace rgm {
/* 汇总各处定义的任务 */
using tasks_ruby =
    core::traits::expand_tuples_t<base::tasks_ruby, rmxp::tasks_ruby,
                                  ext::tasks_ruby>;
using tasks_render =
    core::traits::expand_tuples_t<base::tasks_render, rmxp::tasks_render,
                                  ext::tasks_render>;
using tasks_audio =
    core::traits::expand_tuples_t<base::tasks_audio, rmxp::tasks_audio,
                                  ext::tasks_audio>;
using tasks_table =
    core::traits::expand_tuples_t<base::tasks_table, rmxp::tasks_table,
                                  ext::tasks_table>;

/// @brief 运行逻辑流程的 worker
using worker_ruby_sync =
    core::worker<core::flag_ex<0>, base::kernel_ruby, tasks_ruby>;
/// @brief 运行渲染流程的 worker
using worker_render_sync =
    core::worker<core::flag_ex<1>, core::kernel_passive, tasks_render>;
/// @brief 播放音乐音效的 worker
using worker_audio_sync =
    core::worker<core::flag_ex<2>, core::kernel_passive, tasks_audio>;
/// @brief 进行异步计算的 worker
using worker_table_sync =
    core::worker<core::flag_ex<3>, core::kernel_passive, tasks_table>;

/// @brief 最终引擎由多个 worker 组合而来
using engine_sync_t = core::scheduler<worker_ruby_sync, worker_render_sync,
                                      worker_audio_sync, worker_table_sync>;
/* scheduler_cast 的特化处理 */
RGMENGINE(engine_sync_t);

/* 异步的 scheduler */
using worker_ruby_async =
    core::worker<core::flag_as<0>, base::kernel_ruby, tasks_ruby>;
using worker_render_async =
    core::worker<core::flag_as<1>, core::kernel_passive, tasks_render>;
using worker_audio_async =
    core::worker<core::flag_as<2>, core::kernel_passive, tasks_audio>;
using worker_table_async =
    core::worker<core::flag_as<3>, core::kernel_passive, tasks_table>;

using engine_async_t = core::scheduler<worker_ruby_async, worker_render_async,
                                       worker_audio_async, worker_table_async>;

RGMENGINE(engine_async_t);

/* 协程的 scheduler */
using worker_ruby_fiber =
    core::worker<core::flag_co<0>, base::kernel_ruby, tasks_ruby>;
using worker_render_fiber =
    core::worker<core::flag_co<1>, core::kernel_passive, tasks_render>;
using worker_audio_fiber =
    core::worker<core::flag_co<2>, core::kernel_passive, tasks_audio>;
using worker_table_fiber =
    core::worker<core::flag_co<3>, core::kernel_passive, tasks_table>;

using engine_fiber_t = core::scheduler<worker_ruby_fiber, worker_render_fiber,
                                       worker_audio_fiber, worker_table_fiber>;

RGMENGINE(engine_fiber_t);
}  // namespace rgm