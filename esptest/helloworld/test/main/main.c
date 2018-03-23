#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include <stdbool.h>

#define try bool _HadError=false;
#define catch(x) ExitJmp:if(_HadError)


void test(){
	printf("Hello world \n");
}

void esp_connection(void *pvParameter){
	esp_bluedroid_enable();
	char *bt_name = "ESP_TEST";
	esp_bt_dev_set_device_name(bt_name);
	esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
	esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, ESP_BT_GAP_MAX_INQ_LEN, 0x01);
	printf("BT visible");

}

void app_main(void)
{
		esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
        
        esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);

		if (esp_bt_controller_init(&bt_cfg) != ESP_OK) {
            printf("fail");
			return;
		}

		if (esp_bt_controller_enable(ESP_BT_MODE_BLE) != ESP_OK) {
            printf("fail");
			return;
		}

		test();
		xTaskCreate(&esp_connection, "esp_connection", 2048, NULL, 5, NULL);

}
