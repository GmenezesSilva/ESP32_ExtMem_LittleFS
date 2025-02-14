#include "main.h"

void app_main(void)
{
    uint32_t id;
    const size_t offset = 0;

    const esp_partition_t *partition_handler;

    const char *partition_label = "ext_storage";

    esp_flash_t *flash_handle;

    spi_bus_config_t bus_config = {
        .mosi_io_num = W25Q128_MOSI,
        .miso_io_num = W25Q128_MISO,
        .sclk_io_num = W25Q128_SCK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };

    esp_flash_spi_device_config_t flash_config = {
        .host_id = W25Q128_SPI,
        .cs_io_num = W25Q128_CS,
        .io_mode = SPI_FLASH_DIO,
        .freq_mhz = 40,
        .input_delay_ns = 0,
        .cs_id = 0,
    };

    esp_vfs_littlefs_conf_t littleFS_config = {
        .base_path = BASE_PATH,
        .partition_label = partition_label,
        .format_if_mount_failed = true,
        .dont_mount = false,
    };

    ESP_ERROR_CHECK(spi_bus_initialize(W25Q128_SPI, &bus_config, SPI_DMA_CH_AUTO));

 
    ESP_LOGI(SPI_TAG, "Canal do DMA utilizado para a memória externa: %d", SPI_DMA_CH_AUTO);

    ESP_ERROR_CHECK(spi_bus_add_flash_device(&flash_handle, &flash_config));

    esp_err_t flash_status = esp_flash_init(flash_handle);
    if (flash_status != ESP_OK)
    {
        ESP_LOGE(MEM_TAG, "Erro ao iniciar a flash como dispositivo: %s", esp_err_to_name(flash_status));
    }
    else{
    ESP_LOGI(MEM_TAG, "Flash externa iniciada com sucesso");
    }

    ESP_ERROR_CHECK(esp_flash_read_id(flash_handle, &id));
    ESP_LOGI(MEM_TAG, "Informações da flash externa, tamanho=%" PRIu32 " KB, ID=0x%" PRIx32, flash_handle->size / 1024, id);

    // Adicionando a partição da memória externa (Revisar caso falhe a criação da partição)
    ESP_LOGI(MEM_TAG, "Adicionando a memória externa como uma partição de nome =\"%s\" com o tamanho total =%" PRIu32 " KB", partition_label, flash_handle->size / 1024);
    ESP_ERROR_CHECK(esp_partition_register_external(flash_handle, offset, flash_handle->size, partition_label, ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, &partition_handler));

    // Registrando o sistema de arquivos LittleFS
    ESP_ERROR_CHECK(esp_vfs_littlefs_register(&littleFS_config));

    size_t total = 0, used = 0;
    esp_err_t ret = esp_littlefs_info(littleFS_config.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(FILE_SYS_TAG, "Failed to get LittleFS partition information (%s)", esp_err_to_name(ret));
        esp_littlefs_format(littleFS_config.partition_label);
    }
    else
    {
        ESP_LOGI(FILE_SYS_TAG, "Partition size: total: %d, used: %d", total, used);

    }

    FILE *test_file;

    test_file = fopen(FILE_PATH, "w");
    if(test_file == NULL)
    {
        ESP_LOGE(FILE_SYS_TAG, "Falha ao abrir o arquivo %s", FILE_PATH);
    }
    else
    {
        ESP_LOGI(FILE_SYS_TAG, "Arquivo %s aberto com sucesso", FILE_PATH);
    }

    fprintf(test_file, "External Memory Test File");
    fclose(test_file);

    struct stat st;
    char text[25] = {0};

    //Verifica se o arquivo existe e imprime informações sobre ele
    if(stat(FILE_PATH, &st) == 0)
    {
        ESP_LOGI(FILE_SYS_TAG, "Arquivo %s encontrado", FILE_PATH);
        ESP_LOGI(FILE_SYS_TAG, "Último acesso: %s", ctime(&st.st_atime));
        ESP_LOGI(FILE_SYS_TAG, "Última modificação: %s", ctime(&st.st_mtime));
    }

    test_file = fopen(FILE_PATH, "r");

    fgets(text, 25, test_file);
    ESP_LOGI(FILE_SYS_TAG, "Texto do arquivo: %s", text);

    while (1)
    {
        /* code */
    }
    
}
