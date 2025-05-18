#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

#define ALL_MOTOR_START() HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_SET);
#define ALL_MOTOR_STOP() HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin, GPIO_PIN_RESET);


#endif