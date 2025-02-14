#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_flash.h"
#include "driver/spi_master.h"
#include "esp_flash_spi_init.h"
#include "esp_partition.h"
#include "esp_system.h"
#include "esp_littlefs.h"
#include "sys/stat.h"

/* Periférico SPI */
#define W25Q128_SPI  SPI3_HOST
/* Pinos*/
#define W25Q128_CS   GPIO_NUM_35
#define W25Q128_MISO GPIO_NUM_36
#define W25Q128_MOSI GPIO_NUM_37
#define W25Q128_SCK  GPIO_NUM_38

#define BASE_PATH "/littlefs"
#define FILE_PATH "/littlefs/test.txt"


static const char *FILE_SYS_TAG = "littleFS";
static const char *MEM_TAG = "W25Q128";
static const char *SPI_TAG = "SPI";

const char *partition_name = "ext_storage";


#endif // _MAIN_H_