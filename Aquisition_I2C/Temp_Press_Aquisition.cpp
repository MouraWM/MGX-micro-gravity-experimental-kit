#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

// Definições de endereço I2C
#define BMP280_ADDR  0x76

// Inicialização e leitura do BMP280
void initBMP280(int fd) {
    wiringPiI2CWriteReg8(fd, 0xF4, 0x2F); // Configurar o modo de operação
    wiringPiI2CWriteReg8(fd, 0xF5, 0x0C); // Configurar o filtro
}

void readBMP280(int fd, int32_t &temp, int32_t &press) {
    // Leitura dos registradores de temperatura e pressão
    temp = (wiringPiI2CReadReg8(fd, 0xFA) << 12) | (wiringPiI2CReadReg8(fd, 0xFB) << 4) | (wiringPiI2CReadReg8(fd, 0xFC) >> 4);
    press = (wiringPiI2CReadReg8(fd, 0xF7) << 12) | (wiringPiI2CReadReg8(fd, 0xF8) << 4) | (wiringPiI2CReadReg8(fd, 0xF9) >> 4);
}

int main() {
    // Inicialização do wiringPi
    wiringPiSetup();

    // Inicialização dos sensores I2C
    int bmp280_fd = wiringPiI2CSetup(BMP280_ADDR);
    if (bmp280_fd == -1) {
        perror("Failed to initialize I2C devices");
        exit(EXIT_FAILURE);
    }

    initBMP280(bmp280_fd);

    // Variáveis para armazenar os dados dos sensores
    int32_t temp, press;

    while (true) {
        // Leitura do sensor BMP280
        readBMP280(bmp280_fd, temp, press);

        // Imprimir os dados lidos
        std::cout << "Temp: " << temp << std::endl;
        std::cout << "Press: " << press << std::endl;

        sleep(1); // Aguardar 1 segundo antes da próxima leitura
    }

    return 0;
}

