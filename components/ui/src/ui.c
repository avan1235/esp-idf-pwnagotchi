#include <esp_log.h>
#include <string.h>
#include <sys/param.h>

#include "ui.h"
#include "u8g2_esp32_hal.h"

#define MAX_LINE_CHARS 15

static const char *TAG = "ui";

void init_screen(u8g2_t *u8g2) {
    ESP_LOGD(TAG, "init screen");

    u8g2_esp32_hal_init_default();

    // init u8g2 structure
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(
            u8g2,
            U8G2_R0,
            u8g2_esp32_i2c_byte_cb,
            u8g2_esp32_gpio_and_delay_cb
    );
    u8x8_SetI2CAddress(&u8g2->u8x8, CONFIG_I2C_ADDRESS << 1);

    // send init sequence to the display, display is in
    // sleep mode after this
    u8g2_InitDisplay(u8g2);

    // wake up display
    u8g2_SetPowerSave(u8g2, 0);
}

void show_menu_items(u8g2_t *u8g2, menu_items_t *items) {
    u8g2_ClearBuffer(u8g2);
    u8g2_SetFont(u8g2, u8g2_font_5x8_tr);

    for (size_t i = 0; i < items->count; ++i) {
        char line[MAX_LINE_CHARS] = {' '};
        memcpy(line, items->items[i], MIN(strlen(items->items[i]), MAX_LINE_CHARS));

        u8g2_DrawStr(u8g2, 4, i * 8 + 8, line);
        if (i == items->selected) {
            u8g2_DrawBox(u8g2, 1, i * 8, 2, 8);
        }
    }
    u8g2_SendBuffer(u8g2);
}
