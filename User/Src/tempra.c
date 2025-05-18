#include "stdio.h"
#include "main.h"
#include "MLX90640_API.h"
#include "usart.h"

#include "tempra.h"

static void MX_GPIO_Init(void);

uint8_t data_buf[1544]; // 设置传入buffer大小

uint32_t CheckCode;

/* 主要程序 */

void mlx()
{

    int16_t temp = 0, rest_count = 0;
    float Temperature = 0;
    float min_temp = 500, max_temp = 0;
    int state = 0;

    // uart 接受0-1543byte的数据

    data_buf[0] = 0x5A;
    data_buf[1] = 0x5A;
    data_buf[2] = 0x02;
    data_buf[3] = 0x06;

    MLX90640_SetRefreshRate(MLX_I2C_ADDR, RefreshRate);
    MLX90640_SetChessMode(MLX_I2C_ADDR);
    MLX90640_DumpEE(MLX_I2C_ADDR, frame);
    MLX90640_ExtractParameters(frame, &mlx90640);

    for (int i = 0; i < 10; i++) // 丢去开始帧
    {
        MLX90640_GetFrameData(MLX_I2C_ADDR, frame);
    }

    while (1)
    {
        static uint16_t i;
        MLX90640_GetFrameData(MLX_I2C_ADDR, frame);
        // 计算温度数据
        Ta = MLX90640_GetTa(frame, &mlx90640);
        tr = Ta - TA_SHIFT;
        emissivity = 0.95; // 发射率
        MLX90640_CalculateTo(frame, &mlx90640, emissivity, tr, mlx90640To);

        CheckCode = 0x5A5A;
        CheckCode += 0x0602;

        for (i = 0; i < 768; i++) // 放大100倍，转换成INT16,先发送 目标温度 低8，高后8，DMA循环发送至调试用CH340端口usart1
        {
            data_buf[i * 2 + 4] = (uint16_t)(mlx90640To[i] * 100) & 0xFF;
            data_buf[i * 2 + 5] = ((uint16_t)(mlx90640To[i] * 100) >> 8) & 0xFF;
            CheckCode += (uint16_t)(mlx90640To[i] * 100);
        }
        data_buf[1540] = (uint16_t)(Ta * 100) & 0xFF;        // 自身温度低8位
        data_buf[1541] = ((uint16_t)(Ta * 100) >> 8) & 0xFF; // 自身温度高8位
        CheckCode += (uint16_t)(Ta * 100);                   // 检查目标温度是否异常
        data_buf[1542] = (uint16_t)CheckCode & 0xFF;         // 校验和低8位
        data_buf[1543] = ((uint16_t)CheckCode >> 8) & 0xFF;  // 校验和高8位

        HAL_UART_Transmit_DMA(&huart1, data_buf, 1544); // 开启DMA传输，至usart1的CH340

        HAL_GPIO_TogglePin(Board_LED_G_Pin, Board_LED_G_Pin); // PC12:自定义板载LED

        if (Ta >= tr)
        {
            printf("检测到有大于环境温度的物体！");
            return tempra = 1;
        }
        else if (Ta <= tr)
        {
            return tempra = 0;
        }
    }
}