#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

// Inicialização e leitura do GPS GY-NEO6MV2
int initGPS() {
    int serial_port = open("/dev/ttyTHS1", O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_port == -1) {
        perror("Unable to open /dev/ttyTHS1");
        exit(EXIT_FAILURE);
    }
    struct termios options;
    tcgetattr(serial_port, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(serial_port, TCSANOW, &options);
    return serial_port;
}

void readGPS(int serial_port, char *buffer, int buffer_size) {
    memset(buffer, 0, buffer_size);
    int length = read(serial_port, buffer, buffer_size - 1);
    if (length < 0) {
        perror("Failed to read from the serial port");
    }
}

int main() {
    // Inicialização do GPS
    int gps_fd = initGPS();
    char gps_buffer[256];

    while (true) {
        // Leitura do GPS
        readGPS(gps_fd, gps_buffer, sizeof(gps_buffer));

        // Imprimir os dados lidos
        std::cout << "GPS: " << gps_buffer << std::endl;

        sleep(1); // Aguardar 1 segundo antes da próxima leitura
    }

    close(gps_fd);
    return 0;
}

