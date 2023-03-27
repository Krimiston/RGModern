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
#include "base/base.hpp"
#include "driver.hpp"
#include "rmxp/builtin.hpp"

namespace rgm::shader {
template <size_t driver>
struct shader_base {
  static void setup(cen::renderer&) {}
};

template <size_t driver, template <size_t> class T_shader>
struct shader_static : shader_base<driver> {
  static void setup(cen::renderer&) {}
};

template <size_t driver, template <size_t> class T_shader>
struct shader_dynamic : shader_base<driver> {
  static void setup(cen::renderer&) {}
};

template <size_t driver>
struct shader_gray : shader_static<driver, shader_gray> {
  explicit shader_gray() {}
};

template <size_t driver>
struct shader_hue : shader_dynamic<driver, shader_hue> {
  explicit shader_hue(int) {}
};

template <size_t driver>
struct shader_tone : shader_dynamic<driver, shader_tone> {
  explicit shader_tone(rmxp::tone) {}
};

template <size_t driver>
struct shader_transition : shader_dynamic<driver, shader_transition> {
  explicit shader_transition(double, int) {}
};
}  // namespace rgm::shader