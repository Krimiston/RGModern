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
#include "base/base.hpp"
#include "builtin.hpp"
#include "drawable.hpp"

namespace rgm::rmxp {
/**
* @brief 创建 viewport 通用的 ruby 方法
* @note 方法包括：
* 1. create，创建 viewport，添加到 drawables 中
* 2. dispose，将 viewport 从 drawables 中移除，释放相关资源，
     同时释放所有绑定到该 viewport 的其他 drawable
* 3. set_z，修改 viewport 的 z 值
* 4. refresh_value，同步更新值类型的属性
*/
struct init_viewport {
  static void before(auto& this_worker) {
    static decltype(auto) worker = this_worker;

    struct wrapper {
      static VALUE create(VALUE, VALUE viewport_) {
        drawables& data = RGMDATA(drawables);
        id2z& cache_z = RGMDATA(id2z);

        z_index v_zi;
        viewport v;
        v_zi << viewport_;
        v << viewport_;
        cache_z.insert({v_zi.id, v_zi.z});
        data.emplace(std::move(v_zi), std::move(v));
        return Qnil;
      }

      static VALUE dispose(VALUE, VALUE id_) {
        drawables& data = RGMDATA(drawables);
        id2z& cache_z = RGMDATA(id2z);

        RGMLOAD(id, uint64_t);

        auto it = cache_z.find(id);

        // 如果 cache_z 中没有这个 id，那么相应的 viewport 已经析构。
        if (it == cache_z.end()) return Qnil;

        int z = it->second;
        cache_z.erase(it);
        // 从 cache_z 中移除所有内部元素
        drawable& item = data[z_index{z, id}];
        viewport& v = std::get<viewport>(item);
        for (auto& [sub_zi, sub_item] : v.m_data) {
          cache_z.erase(sub_zi.id);
        }
        v.m_data.clear();
        // 从 drawables 中移除 viewport，此后 m_data 也会析构
        data.erase(z_index{z, id});
        return Qnil;
      }

      static VALUE set_z(VALUE, VALUE viewport_, VALUE z_) {
        drawables& data = RGMDATA(drawables);
        id2z& cache_z = RGMDATA(id2z);

        z_index zi;
        zi << viewport_;

        // Check_Type(z_, T_FIXNUM);
        RGMLOAD(z, int);
        int new_z = z;

        auto it = cache_z.find(zi.id);
        if (it == cache_z.end()) return z_;
        it->second = new_z;

        data.set_z(zi, new_z);
        return z_;
      }

      static VALUE refresh_value(VALUE, VALUE viewport_, VALUE type_) {
        drawables& data = RGMDATA(drawables);
        z_index zi;
        zi << viewport_;

        Check_Type(type_, T_FIXNUM);
        auto type = static_cast<word>(FIX2INT(type_));

        viewport& v = std::get<viewport>(data[zi]);
        v.refresh_value(type);
        return Qnil;
      }
    };

    VALUE rb_mRGM = rb_define_module("RGM");
    VALUE rb_mRGM_Base = rb_define_module_under(rb_mRGM, "Base");
    rb_define_module_function(rb_mRGM_Base, "viewport_create", wrapper::create,
                              1);
    rb_define_module_function(rb_mRGM_Base, "viewport_dispose",
                              wrapper::dispose, 1);
    rb_define_module_function(rb_mRGM_Base, "viewport_set_z", wrapper::set_z,
                              2);
    rb_define_module_function(rb_mRGM_Base, "viewport_refresh_value",
                              wrapper::refresh_value, 2);
  }
};
}  // namespace rgm::rmxp