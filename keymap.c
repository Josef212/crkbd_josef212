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

enum tap_dance_keys
{
    TD_PC, 
    TD_COMI, 
    TD_SLA, 
    TD_CAPLOCK, 
    TD_ALT 
};

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
    [L_QWERTY] = LAYOUT(
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

    [L_LOWER] = LAYOUT(
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

    [L_RAISE] = LAYOUT(
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

    [L_ADJUST] = LAYOUT(
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

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// LEDS
#ifdef RGB_MATRIX_ENABLE

int RGB_current_mode;

void suspend_power_down_user(void) { rgb_matrix_set_suspend_state(true); }
void suspend_wakeup_init_user(void) { rgb_matrix_set_suspend_state(false); }

void matrix_init_user(void) 
{
    RGB_current_mode = rgblight_config.mode;
}

// TODO: This is not being triggered...
void rgb_matrix_indicators_user(void) 
{
    #ifdef OLED_DRIVER_ENABLE
    static char tmp[24];
    snprintf(
        tmp, sizeof(tmp),
        "TMP: %ld - %ld\n",
        layer_state, biton32(layer_state)
    );

    oled_write(tmp, false);
    #endif

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
            if (host_keyboard_leds() & ( 1 << USB_LED_CAPS_LOCK)) 
            {
                for (int i = 0; i < DRIVER_LED_TOTAL; i++) 
                {
                    rgb_matrix_set_color(i, 0, 255, 0);
                }
            }
            break;
    }
}

#endif

// ----------------
// OLED
#ifdef OLED_DRIVER_ENABLE

#define L_DEFAULT_BIT 0
#define L_LOWER_BIT 2
#define L_RAISE_BIT 4
#define L_ADJUST_BIT 8

char keyLog[24] = {};
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

void OledRenderKeylog(void) { oled_write(keyLog, false); }
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
        keyLog, sizeof(keyLog), 
        "%dx%d - k%2d : %c",
        record->event.key.row, 
        record->event.key.col, 
        keycode, name
    );
}

void OledRenderLayerState(void)
{
    static char layerStr[24];
    snprintf(
        layerStr, sizeof(layerStr),
        "Layer: %ld - ",
        layer_state
    );

    oled_write(layerStr, false);
    
    switch(layer_state)
    {
        case L_DEFAULT_BIT: oled_write_P(PSTR("QWERTY\n"), false); break;
        case L_LOWER_BIT: oled_write_P(PSTR("LOWER\n"), false); break;
        case L_RAISE_BIT: oled_write_P(PSTR("RAISE\n"), false); break;
        case L_ADJUST_BIT:
        case L_ADJUST_BIT | L_LOWER_BIT:
        case L_ADJUST_BIT | L_RAISE_BIT:
        case L_ADJUST_BIT | L_LOWER_BIT | L_RAISE_BIT: 
            oled_write_P(PSTR("ADJUST\n"), false); break;
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
    {
        OledRenderLayerState();
        OledRenderKeylog();
    }
    else
    {
        OledRenderLayerState();
    }
}
#endif // OLED_DRIVER_ENABLE

// ----------------

void UpdateLayer(uint8_t l, bool set)
{
    if(set)
        layer_on(l);
    else
        layer_off(l);

    if(IS_LAYER_ON(L_LOWER) && IS_LAYER_ON(L_RAISE))
        layer_on(L_ADJUST);
    else
        layer_off(L_ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) 
{
#ifdef OLED_DRIVER_ENABLE
    oled_timer = timer_read32();
#endif

    if(record->event.pressed)
        SetKeylog(keycode, record);

    bool swallow = false;
    switch(keycode)
    {
        case LOWER:
            UpdateLayer(L_LOWER, record->event.pressed);
            swallow = true;
        break;

        case RAISE:
            UpdateLayer(L_RAISE, record->event.pressed);
            swallow = true;
        break;

        case ADJUST:
            if(record->event.pressed)
                layer_on(L_ADJUST);
            else
                layer_off(L_ADJUST);

            swallow = true;
        break;
    }

    return !swallow;
}