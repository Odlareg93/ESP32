deps_config := \
	/home/geraldo/esp/esp-idf/components/app_trace/Kconfig \
	/home/geraldo/esp/esp-idf/components/aws_iot/Kconfig \
	/home/geraldo/esp/esp-idf/components/bt/Kconfig \
	/home/geraldo/esp/esp-idf/components/esp32/Kconfig \
	/home/geraldo/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/geraldo/esp/esp-idf/components/ethernet/Kconfig \
	/home/geraldo/esp/esp-idf/components/fatfs/Kconfig \
	/home/geraldo/esp/esp-idf/components/freertos/Kconfig \
	/home/geraldo/esp/esp-idf/components/heap/Kconfig \
	/home/geraldo/esp/esp-idf/components/libsodium/Kconfig \
	/home/geraldo/esp/esp-idf/components/log/Kconfig \
	/home/geraldo/esp/esp-idf/components/lwip/Kconfig \
	/home/geraldo/esp/esp-idf/components/mbedtls/Kconfig \
	/home/geraldo/esp/esp-idf/components/openssl/Kconfig \
	/home/geraldo/esp/esp-idf/components/pthread/Kconfig \
	/home/geraldo/esp/esp-idf/components/spi_flash/Kconfig \
	/home/geraldo/esp/esp-idf/components/spiffs/Kconfig \
	/home/geraldo/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/geraldo/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/geraldo/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/geraldo/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/geraldo/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/geraldo/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
