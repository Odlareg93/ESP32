#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs_flash.h"

#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"

#define PROFILE_NUM 1
#define PROFILE_APP_ID 0
#define GATTS_TAG "GATTS"

static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

struct gatts_profile_inst {
    esp_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_handle;
    esp_gatt_srvc_id_t service_id;
    uint16_t char_handle;
    esp_bt_uuid_t char_uuid;
    esp_gatt_perm_t perm;
    esp_gatt_char_prop_t property;
    uint16_t descr_handle;
    esp_bt_uuid_t descr_uuid;
};

static struct gatts_profile_inst gl_profile_tab[PROFILE_NUM] = {
	[PROFILE_APP_ID] = {
        .gatts_cb = gatts_profile_event_handler,
        .gatts_if = ESP_GATT_IF_NONE,
	},
};

typedef struct {
    bool set_scan_rsp;
    bool include_name;
    bool include_txpower;
    int min_interval;
    int max_interval;
    int appearance;
    uint16_t manufacturer_len;
    uint8_t *p_manufacturer_data;
    uint16_t service_data_len;
    uint8_t *p_service_data;
    uint16_t service_uuid_len;
    uint8_t *p_service_uuid;
    uint8_t flag;
} esp_ble_adv_data_t;

//static uint8_t service_uuid[32] = {};

static esp_ble_adv_data_t adv_data = {
	.set_scan_rsp = false,
	.include_name = true,
	.include_txpower = true,
	.min_interval = 0x20,
	.max_interval = 0x40,
	.appearance = 0x00,
	.manufacturer_len = 0, //TEST_MANUFACTURER_DATA_LEN,
	.p_manufacturer_data =  NULL, //&test_manufacturer[0],
	.service_data_len = 0,
	.p_service_data = NULL,
	//.service_uuid_len = 32,
	//.p_service_uuid = adv_service_uuid128,
	.flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static void gatts_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {

	switch(event){
	}
}

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param){
	switch(event){
		case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
	        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
	            ESP_LOGE(GATTS_TAG, "Advertising start failed\n");
	        }
	        break;
	    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
	        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
	            ESP_LOGE(GATTS_TAG, "Advertising stop failed\n");
	        }
	        else {
	            ESP_LOGI(GATTS_TAG, "Stop adv successfully\n");
	        }
	        break;
	    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
	        param->update_conn_params.status;
			param->update_conn_params.min_int;
			param->update_conn_params.max_int;
			param->update_conn_params.conn_int;
			param->update_conn_params.latency;
			param->update_conn_params.timeout;
	        break;
	    default:
	        break;
	}
}
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) {
            gl_profile_tab[param->reg.app_id].gatts_if = gatts_if;
        } else {
        	param->reg.app_id;
			param->reg.status;
            return;
        }
    }
    do {
        int idx;
        for (idx = 0; idx < PROFILE_NUM; idx++) {
            if (gatts_if == ESP_GATT_IF_NONE || gatts_if == gl_profile_tab[idx].gatts_if) {
                if (gl_profile_tab[idx].gatts_cb) {
                    gl_profile_tab[idx].gatts_cb(event, gatts_if, param);
                }
            }
        }
    } while (0);
}
typedef struct {
    uint16_t adv_int_min;
    uint16_t adv_int_max;

    esp_ble_adv_type_t adv_type;
    esp_ble_addr_type_t own_addr_type;
    esp_bd_addr_t peer_addr;
    esp_ble_addr_type_t peer_addr_type;
    esp_ble_adv_channel_t channel_map;
    esp_ble_adv_filter_t adv_filter_policy;
}
esp_ble_adv_params_t;

static esp_ble_adv_params_t ble_params = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy  = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

void app_main(void)
{
	  esp_err_t ret = nvs_flash_init();
	 if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
		 ESP_ERROR_CHECK(nvs_flash_erase());
	     ret = nvs_flash_init();
	 }
	 ESP_ERROR_CHECK(ret);

	 esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	 ret = esp_bt_controller_init(&bt_cfg);
	 if (ret) {
		 ESP_LOGE(GATTS_TAG, "%s initialize controller failed\n", __func__);
	     return;
	 }

	 ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
	 if (ret) {
		 ESP_LOGE(GATTS_TAG, "%s enable controller failed\n", __func__);
		 return;
	 }
	 ret = esp_bluedroid_init();
	 if (ret) {
		 ESP_LOGE(GATTS_TAG, "%s init bluetooth failed\n", __func__);
		 return;
	 }
	 ret = esp_bluedroid_enable();
	 if (ret) {
		 ESP_LOGE(GATTS_TAG, "%s enable bluetooth failed\n", __func__);
		 return;
	 }

	 esp_ble_gap_start_advertising(&ble_params);
	 esp_ble_gatts_register_callback(gatts_event_handler);
	 esp_ble_gap_register_callback(gap_event_handler);
	 esp_ble_gap_config_adv_data(&adv_data);

}
