#include "main.h"
#include "spi.h"
#include "receive.h"

int receive()
{
    // 此处为接受主机的数据的实现：包含手动触发、检测到手触发
    if (SPI_CR1_BIDIMODE)
    {
        HAL_SPI_Receive(SPI1, receive_buffer, 8, HAL_MAX_DELAY); // 目前是接收到任何东西都能触发，以后改
        allow = 1;
    }
    else
    {
        allow = 0;
    }
    return allow;
}