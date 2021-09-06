 /* Copyright 2015-2017 Christon DeWan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define USERSPACE

#ifndef XTONHASVIM_MOD_H
#define XTONHASVIM_MOD_H

#include QMK_KEYBOARD_H
#include "action_layer.h"

#define X_____X KC_NO

enum xtonhasvim_keycodes {
  // 20: give keyboard-specific codes some room
  FIREY_RETURN = SAFE_RANGE + 20,  // kick off special effects
  VIM_START, // bookend for vim states
  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_H,
  VIM_G,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VS, // visual-line
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  VIM_PERIOD, // to support indent/outdent
  VIM_COMMA,  // and toggle comments
  VIM_SHIFT, // avoid side-effect of supporting real shift.
  VIM_SLASH,
  VIM_WIN_ON,
  VIM_WIN_OFF,
  VIM_XXX,
  VIM_ESC, // bookend
  VIM_SAFE_RANGE // start other keycodes here.
};



bool process_record_vim(uint16_t keycode, keyrecord_t *record);
bool get_is_office_mode(void);
void get_vim_status(char* outStr);

// NOTE: YOU MUST DEFINE THIS
extern uint8_t vim_cmd_layer(void);

extern uint16_t vstate;


#endif
