#ifndef RECEIVE_H
#include "main.h"

int receive();             // receive 函数
uint8_t receive_buffer[8]; // 主机发送的数据为8，可以视情况修改
uint8_t allow;             // 接收到有效数组为1，没接收到或者无效数组为0

#endif