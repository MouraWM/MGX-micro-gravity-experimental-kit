#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

// Definições de endereço I2C
#define MPU9250_ADDR 0x68
#define MAG_ADDR     0x0C

// Inicialização e leitura do MPU9250
void initMPU9250(int fd) {
    wiringPiI2CWriteReg8(fd, 0x6B, 0x00); // Wake up MPU9250
    wiringPiI2CWriteReg8(fd, 0x37, 0x02); // Enable bypass mode for magnetometer access
    wiringPiI2CWriteReg8(fd, 0x6A, 0x00); // Disable I2C Master mode
}

void readMPU9250(int fd, int16_t *accelData, int16_t *gyroData, int16_t *magData) {
    // Leitura dos registradores de aceleração
    accelData[0] = (wiringPiI2CReadReg8(fd, 0x3B) << 8) | wiringPiI2CReadReg8(fd, 0x3C);
    accelData[1] = (wiringPiI2CReadReg8(fd, 0x3D) << 8) | wiringPiI2CReadReg8(fd, 0x3E);
    accelData[2] = (wiringPiI2CReadReg8(fd, 0x3F) << 8) | wiringPiI2CReadReg8(fd, 0x40);

    // Leitura dos registradores de giroscópio
    gyroData[0] = (wiringPiI2CReadReg8(fd, 0x43) << 8) | wiringPiI2CReadReg8(fd, 0x44);
    gyroData[1] = (wiringPiI2CReadReg8(fd, 0x45) << 8) | wiringPiI2CReadReg8(fd, 0x46);
    gyroData[2] = (wiringPiI2CReadReg8(fd, 0x47) << 8) | wiringPiI2CReadReg8(fd, 0x48);

    // Leitura dos registradores do magnetômetro
    wiringPiI2CWriteReg8(fd, 0x0A, 0x01); // Enable magnetometer
    magData[0] = (wiringPiI2CReadReg8(fd, 0x03) << 8) | wiringPiI2CReadReg8(fd, 0x04);
    magData[1] = (wiringPiI2CReadReg8(fd, 0x05) << 8) | wiringPiI2CReadReg8(fd, 0x06);
    magData[2] = (wiringPiI2CReadReg8(fd, 0x07) << 8) | wiringPiI2CReadReg8(fd, 0x08);
}

int main() {
    // Inicialização do wiringPi
    wiringPiSetup();

    // Inicialização dos sensores I2C
    int mpu9250_fd = wiringPiI2CSetup(MPU9250_ADDR);
    if (mpu9250_fd == -1) {
        perror("Failed to initialize I2C devices");
        exit(EXIT_FAILURE);
    }

    initMPU9250(mpu9250_fd);

    // Variáveis para armazenar os dados dos sensores
    int16_t accelData[3], gyroData[3], magData[3];

    while (true) {
        // Leitura do sensor MPU9250 
        readMPU9250(mpu9250_fd, accelData, gyroData, magData);

        // Imprimir os dados lidos
        std::cout << "Accel: X=" << accelData[0] << " Y=" << accelData[1] << " Z=" << accelData[2] << std::endl;
        std::cout << "Gyro: X=" << gyroData[0] << " Y=" << gyroData[1] << " Z=" << gyroData[2] << std::endl;
        std::cout << "Mag: X=" << magData[0] << " Y=" << magData[1] << " Z=" << magData[2] << std::endl;

        sleep(1); // Aguardar 1 segundo antes da próxima leitura
    }

    return 0;
}

