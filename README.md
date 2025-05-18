# STM32F4_with_MLX90640

stm32f401rct6 with a motor, MLX90640 the thermal camera and a passive speaker.

as a slave device and work with [STM32F0_with_k210 project](https://github.com/Gulfy034/STM32F0_with_k210).

> [!TIP]
> cmake and [STM32CubeCLT](https://www.st.com.cn/en/development-tools/stm32cubeclt.html) (version >= 6.14.1) needed.
>
> use [STM32CubeMX](https://www.st.com.cn/zh/development-tools/stm32cubemx.html) to open *.ioc project, and use the latest [STM32F4 MCU package](https://www.st.com.cn/zh/embedded-software/stm32cubef4.html#get-software) if you want.
> 
> this is not for Keil MDK project.

## Description

```
typeC serial for debugging(with MLX90640) => USART1 --> PA9:TX, PA10:RX, PC12:LED

MLX90640 the thermal camera(8MHZ,460800bps) => I2C --> PB6:SCL, PB7:SDA

Passive Speaker(PWM) => GPIO --> [TODO]

motor(no signals but with RTN7971B) --> GPIO --> PA1:GPIO-OUTPUT <--> RTN7971B:EN
                                    \-> GPIO --> PC1:GPIO-OUTPUT <--> RTN7971B:IN1

vibrate motor(also with RTN7971B) => GPIO --> PC2:GPIO-OUTPUT <--> RTN7971B:IN2

masterboard => SPI --> PA5:SCK, PA6:MISO, PA7:MOSI

```

## TODO:

- [x] MLX90640 code
- [ ] motor control test
- [ ] master <--> slave board code & test