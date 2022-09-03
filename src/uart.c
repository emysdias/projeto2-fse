#include "../inc/uart.h"

int init_uart()
{
    int uart0_filestream = -1;

    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY); // Open in non blocking read/write mode

    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else
    {
        printf("UART inicializada!\n");
    }

    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; // Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    return uart0_filestream;
}

void write_uart_message_request(int uart, int code)
{
    int codeNumber = 0;
    if (code == DS18B20)
    {
        codeNumber = REQUEST_DS18B20_TEMPERATURE;
    }
    else if (code == POTENTIOMETER)
    {
        codeNumber = REQUEST_POTENTIOMETER_TEMPERATURE;
    }
    else if (code == KEY_STATE)
    {
        codeNumber = REQUEST_KEY_STATE;
    }
    // else if (code == TIMER){
    //     codeNumber = 
    // }

    unsigned char data[7] = {SERVER_CODE, REQUEST_CODE, codeNumber, 5, 9, 6, 6};
    short crc = calcula_CRC(data, 7);

    unsigned char message[9];
    memcpy(message, &data, 7);
    memcpy(&message[7], &crc, 2);

    if (uart != -1)
    {
        int count = write(uart, &message[0], 9);

        if (count < 0)
        {
            printf("UART TX error!\n");
        }
    }

    sleep(1);
}

void write_uart_message_send(int uart, int control_signal)
{
    unsigned char data[7] = {SERVER_CODE, SEND_CODE, SEND_CONTROL_SIGNAL, 5, 9, 6, 6};
    unsigned char message[13];

    memcpy(message, &data, 7);
    memcpy(&message[7], &control_signal, 4);

    short crc = calcula_CRC(message, 11);
    memcpy(&message[11], &crc, 2);

    if (uart != -1)
    {
        int count = write(uart, &message[0], 13);

        if (count < 0)
        {
            printf("UART TX error!\n");
        }
    }

    sleep(1);
}

// void write_uart_message_send_teste(int uart, int control_signal)
// {
//     unsigned char data[7] = {SERVER_CODE, SEND_CODE, SEND_CONTROL_TEMPERATURE, 5, 9, 6, 6};
//     unsigned char message[13];

//     memcpy(message, &data, 7);
//     memcpy(&message[7], &control_signal, 4);

//     short crc = calcula_CRC(message, 11);
//     memcpy(&message[11], &crc, 2);

//     if (uart != -1)
//     {
//         int count = write(uart, &message[0], 13);

//         if (count < 0)
//         {
//             printf("UART TX error!\n");
//         }
//     }

//     sleep(1);
// }

float read_uart_message_temperature(int uart)
{
    float response = -1.0;
    //-------------- CHECK FOR ANY RX BYTES --------------
    if (uart != -1)
    {
        // Read up to 255 characters from the port if they are there
        unsigned char rx_buffer[20];
        int rx_length = read(uart, rx_buffer, 20);

        if (rx_length < 0)
        {
            printf("Erro na leitura! RX_LENGTH: %d\n", rx_length);
            response = -1;
        }
        else if (rx_length == 0)
        {
            printf("Nenhum dado disponível.\n");
            response = -1;
        }
        else
        {
            rx_buffer[rx_length] = '\0';
            memcpy(&response, &rx_buffer[3], sizeof(float));
        }
    }

    return response;
}

int read_uart_message_key_state(int uart)
{
    int response = -1;
    //-------------- CHECK FOR ANY RX BYTES --------------
    if (uart != -1)
    {
        // Read up to 255 characters from the port if they are there
        unsigned char rx_buffer[256];
        int rx_length = read(uart, (void *)rx_buffer, 255);

        if (rx_length < 0)
        {
            printf("Erro na leitura! RX_LENGTH: %d\n", rx_length);
            response = -1;
        }
        else if (rx_length == 0)
        {
            printf("Nenhum dado disponível.\n");
            response = -1;
        }
        else
        {
            rx_buffer[rx_length] = '\0';
            int data;
            memcpy(&data, &rx_buffer[3], 4);
            response = data;
        }
    }

    return response;
}

float potentiometer_temperature(int uart, float TR)
{
    write_uart_message_request(uart, POTENTIOMETER);

    float TR_temp = read_uart_message_temperature(uart);

    if (TR_temp < 0)
    {
        TR_temp = TR;
    }
    printf("TR: %f\n", TR_temp);

    return TR_temp;
}

float DS18B20_temperature(int uart, float TI)
{
    write_uart_message_request(uart, DS18B20);

    float TI_temp = read_uart_message_temperature(uart);

    if (TI_temp < 0)
    {
        TI_temp = TI;
    }

    printf("TI: %f\n", TI_temp);
    return TI_temp;
}

// float timer(int uart, float TI)
// {
//     write_uart_message_request(uart, TIMER);

//     float TI_temp = read_uart_message_temperature(uart);

//     if (TI_temp < 0)
//     {
//         TI_temp = TI;
//     }

//     printf("TI: %f\n", TI_temp);
//     return TI_temp;
// }

int get_key_state(int uart)
{
    write_uart_message_request(uart, KEY_STATE);

    int key_state = read_uart_message_key_state(uart);

    return key_state;
}

void send_control_signal(int uart, int control_signal)
{
    write_uart_message_send(uart, control_signal);
}

void close_uart(int uart)
{
    close(uart);
}