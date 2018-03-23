#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>
#include <stdio.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include <stdbool.h>


void test(){
	printf("bt controller init and enable\n");
}

void esp_connection(void *pvParameter){
	char *bt_name = "ESP_TEST";
	if (esp_bluedroid_init() != ESP_OK){
		return;
	}
	esp_bluedroid_enable();
	esp_bt_dev_set_device_name(bt_name);
	esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
	esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, ESP_BT_GAP_MAX_INQ_LEN, 0x01);
	printf("BT visible");

}

void app_main(void)
{
		esp_bt_controller_config_t bt_conf = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
        
		if (esp_bt_controller_init(&bt_conf) != ESP_OK) {
			return;
		}

		if (esp_bt_controller_enable(ESP_BT_MODE_BTDM) != ESP_OK) {
			return;
		}

		test();
		xTaskCreate(&esp_connection, "esp_connection", 2048, NULL, 5, NULL);

}
