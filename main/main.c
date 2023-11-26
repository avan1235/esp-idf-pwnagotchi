#include <esp_types.h>
#include <nvs_flash.h>
#include <memory.h>

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include "esp_log.h"
#include "esp_event.h"

#include "wifi_controller.h"
#include "../components/ui/interface/ui.h"

#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>

#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"


static const char *TAG = "main";


void app_main(void) {
    ESP_LOGD(TAG, "app_main started");
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(nvs_flash_init());

    wifi_init_sta();

    u8g2_t screen;
    init_screen(&screen);

    const char *options[] = {
            "First entry",
            "Second entry",
            "Third entry",
    };

    menu_items_t items = {
            .items = options,
            .selected = 0,
            .count = 3,
    };

    while (true) {
        show_menu_items(&screen, &items);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        items.selected += 1;
        items.selected %= items.count;
    }

//    while (true) {
//        ESP_LOGI(TAG, "Start scanning nearby APs...");
//        wifictl_scan_nearby_aps();
//
//        const wifictl_ap_records_t *ap_records;
//        ap_records = wifictl_get_ap_records();
//
//        // 33 SSID + 6 BSSID + 1 RSSI
//        char resp_chunk[40];
//        ssd1306_software_scroll(&screen, 0, (screen._pages - 1));
//
//        for (unsigned i = 0; i < ap_records->count; i++) {
//            memcpy(resp_chunk, ap_records->records[i].ssid, 33);
//            memcpy(&resp_chunk[33], ap_records->records[i].bssid, 6);
//            memcpy(&resp_chunk[39], &ap_records->records[i].rssi, 1);
//
//            ssd1306_scroll_text(&screen, resp_chunk, 40, false);
//        }
//        vTaskDelay(10000 / portTICK_PERIOD_MS);
//    }
}
