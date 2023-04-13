// zlib License

// copyright (C) 2023 Guoxiaomi and Krimiston

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

namespace rgm::ext {
struct textinput_start {
  int x;
  int y;
  int width;
  int height;

  void run(auto&) {
    cen::log_warn("[Input] text input is started");

    SDL_StartTextInput();
    SDL_Rect r{x, y, width, height};
    SDL_SetTextInputRect(&r);
  }
};

struct textinput_stop {
  void run(auto&) {
    cen::log_warn("[Input] text input is stopped");

    SDL_SetTextInputRect(NULL);
    SDL_StopTextInput();
  }
};

struct textinput_state {
  std::string text;
  int position;

  VALUE rb_cTextBox;
  ID rb_sym_need_refresh;

  void setup() {
    VALUE rb_mRGM = rb_define_module("RGM");
    VALUE rb_mRGM_EXT = rb_define_module_under(rb_mRGM, "Ext");
    rb_cTextBox = rb_define_class_under(rb_mRGM_EXT, "TextBox", rb_cObject);
    rb_sym_need_refresh = rb_intern("@@need_refresh");
  }

  void refresh() { rb_cvar_set(rb_cTextBox, rb_sym_need_refresh, Qtrue); }
};

struct text_input {
  std::string text;

  void run(auto& worker) {
    textinput_state& ci = RGMDATA(textinput_state);
    ci.text = text;
    ci.position = -1;
    ci.refresh();
  }
};

struct text_edit {
  std::string text;
  int pos;

  void run(auto& worker) {
    textinput_state& ci = RGMDATA(textinput_state);
    ci.text = text;
    ci.position = pos;
    ci.refresh();
  }
};

struct init_event {
  static void before(auto& worker) {
    base::cen_library::event_dispatcher_t& d =
        RGMDATA(base::cen_library).event_dispatcher;

    d.bind<cen::text_editing_event>().to(
        [&worker](const cen::text_editing_event& e) {
          cen::log_debug("[Input] text edit\n");

          worker >> text_edit{std::string{e.text()}, e.start()};
        });

    d.bind<cen::text_input_event>().to(
        [&worker](const cen::text_input_event& e) {
          cen::log_info("[Input] text input '%s'\n", e.text_utf8().data());

          worker >> text_input{std::string{e.text_utf8()}};
        });
  }
};

struct init_textinput {
  using data = std::tuple<textinput_state>;

  static void before(auto& this_worker) {
    static decltype(auto) worker = this_worker;

    /** wrapper 类，创建静态方法供 ruby 的模块绑定 */
    struct wrapper {
      static VALUE edit_text(VALUE) {
        textinput_state& ci = RGMDATA(textinput_state);

        return rb_utf8_str_new(ci.text.data(), ci.text.length());
      }

      static VALUE edit_pos(VALUE) {
        textinput_state& ci = RGMDATA(textinput_state);

        return INT2FIX(ci.position);
      }

      static VALUE edit_clear(VALUE) {
        textinput_state& ci = RGMDATA(textinput_state);
        ci.text.clear();
        ci.position = 0;
        return Qnil;
      }
    };

    VALUE rb_mRGM = rb_define_module("RGM");
    VALUE rb_mRGM_Ext = rb_define_module_under(rb_mRGM, "Ext");
    rb_define_module_function(rb_mRGM_Ext, "textinput_edit_text",
                              wrapper::edit_text, 0);
    rb_define_module_function(rb_mRGM_Ext, "textinput_edit_pos",
                              wrapper::edit_pos, 0);
    rb_define_module_function(rb_mRGM_Ext, "textinput_edit_clear",
                              wrapper::edit_clear, 0);

    RGMBIND(rb_mRGM_Ext, "textinput_start", textinput_start, 4);
    RGMBIND(rb_mRGM_Ext, "textinput_stop", textinput_stop, 0);

    RGMDATA(textinput_state).setup();
  }
};
}  // namespace rgm::ext