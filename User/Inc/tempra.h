#ifndef TEMPRA_H
#define TEMPRA_H

uint8_t tempra;

#define Rate2HZ 0x02
#define Rate4HZ 0x03
#define Rate8HZ 0x04
#define Rate16HZ 0x05
#define Rate32HZ 0x06

#define MLX_I2C_ADDR 0x33
#define RefreshRate Rate4HZ
#define TA_SHIFT 8 // Default shift for MLX90640 in open air


void mlx();
void SystemClock_Config(void);

uint16_t eeMLX90640[832];
uint16_t frame[834]; // 一帧数据
float Ta, tr;        // 自身温度，环境温度
float emissivity = 0.95;
float mlx90640To[768];
uint16_t i = 0;

#endif