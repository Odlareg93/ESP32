#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_bt.h"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include <stdbool.h>

#define try bool _HadError=false;
#define catch(x) ExitJmp:if(_HadError)


void test(){
	printf("Hello world \n");
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
	return;
}
