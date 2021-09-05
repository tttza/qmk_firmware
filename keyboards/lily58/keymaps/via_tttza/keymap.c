 /* Copyright 2020 Naoki Katahira
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

#include QMK_KEYBOARD_H
#include <eeconfig.h>
#include "keycode.h"
#include "custom_keymap.h"
#include "keymap_extras/keymap_jp.h"
#include "lib/xtonhasvim_mod.h"
#include <twpair_on_jis.h>
#include <oled_render_slave.h>

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _VIM
};

user_config_t user_config = {};

enum custom_keycodes {
  CK_EnJIS = SAFE_RANGE,
  CK_EnUS,
  LOWER,
  RAISE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_DEL, \
                        KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_ENT, RAISE, KC_BSPC, VIM_START \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, \
  KC_ESC, KC_ESC,  _______, KC_CALC, _______, _______, _______, _______,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______, \
                             _______,LGUI(KC_L), _______, _______, _______,  _______, KC_DEL, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_HOME, KC_END,  \
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_RPRN, KC_INS,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PGUP, KC_PGDN, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |TO_US |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |TO_JIS|RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, CK_EnUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, CK_EnJIS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  ),

  [_VIM] = LAYOUT( \
  VIM_ESC, VIM_XXX, VIM_XXX, VIM_XXX, VIM_XXX, VIM_XXX,                   VIM_XXX, VIM_XXX, VIM_XXX, VIM_XXX, VIM_XXX, VIM_XXX,\
  VIM_XXX, VIM_XXX, VIM_W,   VIM_E,   VIM_XXX, VIM_XXX,                   VIM_Y,   VIM_U,   VIM_I,   VIM_O,   VIM_P ,  VIM_XXX, \
  VIM_ESC,   VIM_A, VIM_S,   VIM_D,   VIM_G,   VIM_XXX,                   VIM_H,   VIM_J,   VIM_K,   VIM_L,   VIM_XXX, VIM_XXX, \
  VIM_SHIFT,VIM_XXX,VIM_X,   VIM_C,   VIM_V,   VIM_B,   VIM_XXX, VIM_XXX, VIM_XXX, VIM_XXX, VIM_COMMA,VIM_PERIOD,VIM_XXX,VIM_SHIFT, \
                             _______, _______, _______, _______, _______,  _______, KC_BSPC, _______ \
  )
};


extern uint8_t vim_cmd_layer(void) { return _VIM; }




#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}

char wpm_buffer[3];

char *tochar(uint8_t i, char *p)
{

    if (i / 10 == 0) {
        // No more digits.
        *p++ = i + '0';
        *p = '\0';
        return p;
    }

    p = tochar(i / 10, p);
    *p++ = i % 10 + '0';
    *p = '\0';
    return p;
}


const char *read_logo(void);

static const char PROGMEM vim_logo[] = {
   0,126,195,129,141,145,161,145,141,129,165,189,165,129,189,137,145,137,189,129,195,126,  0,  0,
};

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // Host Keyboard Layer Status

    oled_write(read_logo(), false);
    oled_set_cursor(17, 3);
    if (user_config.jis){
        oled_write_ln("JIS", false);
    } else {
        oled_write_ln(" US", false);
    }

    oled_set_cursor(0, 4);
    if (layer_state_is(vim_cmd_layer())){
        oled_write_raw_P(vim_logo, sizeof(vim_logo));
    } else {
        oled_write("    ", false);
    }

    oled_set_cursor(5, 6);
    uint32_t _layer = get_highest_layer(layer_state);
    oled_write_P(PSTR(" NORM "), _layer == _QWERTY);
    oled_write_ln_P(PSTR(" RAISE "), _layer == _RAISE);
    oled_set_cursor(5, 7);
    oled_write_P(PSTR(" ADJ. "), _layer == _ADJUST);
    oled_write_ln_P(PSTR(" LOWER "), _layer == _LOWER);

  } else {
    render_anim();
    oled_set_cursor(7, 6);
    oled_write_P(PSTR("WPM: "), false);
    tochar(get_current_wpm(), wpm_buffer);
    oled_write(wpm_buffer, false);
    oled_write_P(PSTR("  "), false);
  }
}
#endif // OLED_DRIVER_ENABLE

// -------- variables --------

// Not defined yet.

// -------- EEPROM functions --------

void load_persistent(void) {
    user_config.raw = eeconfig_read_user();
}

void save_persistent(void) {
    eeconfig_update_user(user_config.raw);
}

void eeconfig_init_user(void) {
    save_persistent();
}

void keyboard_post_init_user(void) {
    if (is_keyboard_master()) {
        load_persistent();
    }
}


// -------- Keyboard functions --------

void set_keyboard_lang_to_jis(bool set_jis){
    if ( user_config.jis == set_jis){ return; }
    if (set_jis){
        user_config.jis = 1;
    } else {
        user_config.jis = 0;
    }
    save_persistent();
}

// ref: https://gist.github.com/okapies/5d13a174cbb13ce34dbd9faede9d0b71#file-keymap-c-L99-L164
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
bool process_lower(uint16_t keycode, keyrecord_t *record){
     if (record->event.pressed) {
        lower_pressed = true;
        lower_pressed_time = record->event.time;

        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);

        if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
          register_code(KC_LANG2); // for macOS
          unregister_code(KC_LANG2);
        }
        lower_pressed = false;
      }
      return false;
}
bool process_raise(uint16_t keycode, keyrecord_t *record){
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);

        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
          register_code(KC_HENK);
          unregister_code(KC_HENK);
          register_code(KC_LANG1); // for macOS
          unregister_code(KC_LANG1);
        }
        raise_pressed = false;
      }
      return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
#endif
  }

  if(!process_record_vim(keycode, record)) { return false; }

  switch (keycode) {
    case CK_EnJIS:
        set_keyboard_lang_to_jis(true);
        return false;
    case CK_EnUS:
        set_keyboard_lang_to_jis(false);
        return false;
    case LOWER:
        return process_lower(keycode, record);
    case RAISE:
        return process_raise(keycode, record);
    default:
      if (user_config.jis){
          return twpair_on_jis(keycode, record);
      } else {
          return true;
      }
  }
}

