#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

enum layers 
{ 
    L_QWERTY, 
    L_LOWER, 
    L_RAISE, 
    L_ADJUST 
};

enum custom_keycodes 
{
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    MACRO1,
    MACRO2
};

enum 
{ 
    TD_PC, 
    TD_COMI, 
    TD_SLA, 
    TD_CAPLOCK, 
    TD_ALT 
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = 
{
    // Tap once for ;, twice for :
    [TD_PC] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
    [TD_COMI] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),
    [TD_SLA] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, LSFT(KC_SLSH)),
    [TD_CAPLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_LALT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = 
{
    [L_QWERTY] = LAYOUT_split_3x6_3(
//|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  TD(TD_PC), TD(TD_COMI),
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     TD(TD_CAPLOCK), KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                 KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_SLA), RSFT_T(KC_ENT),
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, LOWER, KC_SPC,     KC_SPC, RAISE, TD(TD_ALT)
                                      //|--------------------------|  |--------------------------|
    ),
    [L_LOWER] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_PWR, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, LALT(KC_G),                   MACRO2 , RALT(KC_PSCR), XXXXXXX,   XXXXXXX,KC_UP, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_SLEP, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLD, KC_MNXT,                     MACRO1 , KC_MYCM, XXXXXXX, KC_LEFT,  KC_DOWN, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         LCTL(KC_LALT), KC_TRNS, KC_SPC,    KC_SPC, RAISE, KC_RALT
                                      //|--------------------------|  |--------------------------|
    ),
    [L_RAISE] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     KC_ESC,  KC_EXLM, KC_AT,  KC_HASH, KC_DLR, KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_F1, KC_F2, KC_F3,   KC_F4, KC_F5, KC_F6,                                KC_MINS, KC_EQL, KC_LBRC,  KC_RBRC, KC_PIPE, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,                               KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, LOWER, KC_SPC,    KC_SPC, KC_TRNS, KC_RALT
                                      //|--------------------------|  |--------------------------|
    ),
    [L_ADJUST] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   RESET,  \
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                        XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, KC_TRNS, KC_SPC,    KC_SPC, KC_TRNS, KC_RALT \
                                      //|--------------------------|  |--------------------------|
    )
};

int RGB_current_mode;

void rgb_matrix_indicators_user(void) 
{
#ifdef RGB_MATRIX_ENABLE
    switch (biton32(layer_state)) 
    {
        case L_RAISE:
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) 
            {
                rgb_matrix_set_color(i, 255, 0, 0);
            }
            break;

        case L_LOWER:
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) 
            {
                rgb_matrix_set_color(i, 0, 0, 255);
            }
            break;

        default:
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) 
            {
                for (int i = 0; i < DRIVER_LED_TOTAL; i++) 
                {
                    rgb_matrix_set_color(i, 0, 255, 0);
                }
            }
    }
#endif
}

#ifdef OLED_DRIVER_ENABLE

#define L_DEFAULT 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

char KeylogStr[24] = {};
const char CodeToName[60] = 
{
    ' ', ' ', ' ', ' ', 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
    'w', 'x', 'y', 'z', 
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', 
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

void SetKeylog(uint16_t keycode, keyrecord_t* record) 
{
    char name = ' ';
    bool outOfRange = 
        (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) 
        || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX);

    if (outOfRange)
        keycode = keycode & 0xFF;

    if (keycode < 60)
        name = CodeToName[keycode];

    // update keylog
    snprintf(
        KeylogStr, sizeof(KeylogStr), 
        "%dx%d, k%2d : %c",
        record->event.key.row, 
        record->event.key.col, 
        keycode, name
    );
}

void OledRenderKeylog(void) { oled_write(KeylogStr, false); }

void OledRenderLayerState(void) 
{
    oled_write_P(PSTR("Layer: "), false);

    switch (layer_state) 
    {
        case L_DEFAULT:
            oled_write_ln_P(PSTR("Default"), false);
            break;

        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;

        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;

        case L_ADJUST:
        case L_ADJUST | L_LOWER:
        case L_ADJUST | L_RAISE:
        case L_ADJUST | L_LOWER | L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }

    if(is_master)
        oled_write_ln_P(PSTR("master"), false);
}

void OledRenderLogo(void) 
{
    static const char PROGMEM crkbdLogo[] = 
    {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 
        0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 
        0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 
        0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 
        0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 
        0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 
        0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 
        0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0
    };

    oled_write_P(crkbdLogo, false);
}

void RenderSpace(void)
{
    oled_write_P(PSTR("     "), false);
}

void OledRenderPrimary(void)
{
    OledRenderLayerState();
    //OledRenderKeylog();
}

void OledRenderSecondary(void)
{
    OledRenderLogo();
}

// ==========================================================================

void render_bootmagic_status(bool status) 
{
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = 
    {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    if (status) 
    {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    }
    else 
    {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) 
{
    // flips the display 180 degrees if offhand
    return !is_master ? OLED_ROTATION_180 : rotation;
}

void oled_task_user(void) 
{
    if (timer_elapsed32(oled_timer) > 1500000) 
    {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else 
    {
        oled_on();
    }
#endif

    if (is_master)
        OledRenderPrimary();
    else 
        OledRenderSecondary();
}
#endif  // OLED_DRIVER_ENABLE

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_user(void) { rgb_matrix_set_suspend_state(true); }
void suspend_wakeup_init_user(void) { rgb_matrix_set_suspend_state(false); }
#endif

/// -------------------------------------------------------------------
/// --------- QMK -----------------------------------------------------
/// -------------------------------------------------------------------

// Initialization
/*
 * void keyboard_pre_init_user(void)
 * void matrix_init_user(void)
 * void keyboard_post_init_user(void)
 */

void matrix_init_user(void) 
{
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

// Events

/// Set layer3 if both mod keys are pressed
void UpdateTriLayerRGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) 
{
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2))
        layer_on(layer3);
    else
        layer_off(layer3);
}

void LayerUpdate(uint8_t layer, bool on)
{
    if(on)
        layer_on(layer);
    else
        layer_off(layer);
    
    UpdateTriLayerRGB(L_LOWER, L_RAISE, L_ADJUST);
}

/// If true returned event is passed to qmk if false event is swallowed
/// https://docs.qmk.fm/#/feature_macros
bool process_record_user(uint16_t keycode, keyrecord_t* record) 
{
#ifdef OLED_DRIVER_ENABLE
    oled_timer = timer_read32();
#endif

    if (record->event.pressed) 
        SetKeylog(keycode, record);

    bool swallow = false;

    switch(keycode)
    {
        case LOWER:
            LayerUpdate(L_LOWER, record->event.pressed);
            swallow = true;
        break;

        case RAISE:
            LayerUpdate(L_RAISE, record->event.pressed);
            swallow = true;
        break;

        case ADJUST:
            if(record->event.pressed)
                layer_on(L_ADJUST);
            else
                layer_off(L_ADJUST);

            swallow = true;
        break;

        case MACRO1: break;
        case MACRO2: break;
    }

    return !swallow;
}
