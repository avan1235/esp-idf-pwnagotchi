#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"

#define tag "SSD1306"

static void reset_screen(SSD1306_t *dev) {
    ssd1306_clear_screen(dev, false);
    ssd1306_contrast(dev, 0xff);
}

static void init_screen(SSD1306_t *dev) {

#if CONFIG_I2C_INTERFACE
    ESP_LOGI(tag, "INTERFACE is i2c");
    ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
    ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
    ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
    i2c_master_init(dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
    ESP_LOGI(tag, "INTERFACE is SPI");
    ESP_LOGI(tag, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
    ESP_LOGI(tag, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
    ESP_LOGI(tag, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
    ESP_LOGI(tag, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
    ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
    spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
    dev._flip = true;
    ESP_LOGW(tag, "Flip upside down");
#endif

    ESP_LOGI(tag, "Panel is 128x64");
    ssd1306_init(dev, 128, 64);

    reset_screen(dev);
}

void app_main(void) {
    SSD1306_t dev;
    char lineChar[20];

    init_screen(&dev);
    reset_screen(&dev);

    ssd1306_software_scroll(&dev, 0, (dev._pages - 1));
    for (int line = 0; line < 100; line++) {
        sprintf(lineChar, "Line %02d", line);
        ssd1306_scroll_text(&dev, lineChar, strlen(lineChar), false);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    // Restart module
    esp_restart();
}
