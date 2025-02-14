# Projeto de Estudo: LittleFS na Memória Externa W25Q128 com ESP32S3

Este projeto tem como objetivo estudar a utilização do sistema de arquivos LittleFS na memória externa W25Q128, utilizando a framework ESP-IDF para o microcontrolador ESP32S3. O projeto implementa a comunicação com a memória externa via SPI e utiliza o componente esp_littlefs para controle do sistema de arquivos na memória flash externa.

## Componentes e Dependências

- **ESP32S3**: Microcontrolador utilizado para o desenvolvimento.
- **W25Q128**: Memória flash externa conectada via SPI.
- **ESP-IDF**: Framework de desenvolvimento para o ESP32.
- [**LittleFS**](https://github.com/joltwallet/esp_littlefs): Sistema de arquivos utilizado para gerenciar os dados armazenados na memória externa.

## Descrição do Projeto

Este projeto configura o uso do sistema de arquivos LittleFS na memória externa W25Q128 conectada ao ESP32S3. O LittleFS foi integrado ao projeto utilizando o componente disponibilizado no component registry da ESP-IDF.

A comunicação com a memória flash externa é realizada via SPI, e o LittleFS gerencia a leitura, escrita e a organização dos dados de forma eficiente na memória externa.

## Arquitetura

- **ESP32S3**: Controla a comunicação SPI com a memória flash W25Q128.
- **LittleFS**: Gerencia o sistema de arquivos na memória externa, proporcionando uma interface para armazenar e acessar dados.
- **Memória Externa W25Q128**: Armazena os dados de forma persistente.

## Considerações

Este projeto foi criado como uma base para o estudo e experimentação com o LittleFS e a memória flash externa no ESP32S3. Não foram adicionados detalhes de implementação específicos de uso do sistema de arquivos, já que o foco é a integração e o estudo do comportamento do sistema de arquivos na memória externa W25Q128. Para mais detalhes sobre o uso do sistema de arquivos acesse a implementação do sistema de arquivos.