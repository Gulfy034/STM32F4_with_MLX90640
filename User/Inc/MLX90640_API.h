//******************************************************************************/	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//酷客热成像开发板
//店铺地址：http://qlqc.taobao.com
//
//  文 件 名   : MLX90640_API.h
//  版 本 号   : v1.0
//  作    者   : wxy

//版权所有，盗版必究。
//Copyright(C) 酷客开发2019-09-24
//All rights reserved

//程序修改：Gulfy034
//******************************************************************************/

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#ifndef _MLX640_API_H_
#define _MLX640_API_H_
    
typedef struct
{
		int16_t kVdd;
		int16_t vdd25;
		float KvPTAT;
		float KtPTAT;
		uint16_t vPTAT25;
		float alphaPTAT;
		int16_t gainEE;
		float tgc;
		float cpKv;
		float cpKta;
		uint8_t resolutionEE;
		uint8_t calibrationModeEE;
		float KsTa;
		float ksTo[4];
		int16_t ct[4];
		float alpha[768];    
		int16_t offset[768];    
		float kta[768];    
		float kv[768];
		float cpAlpha[2];
		int16_t cpOffset[2];
		float ilChessC[3]; 
		uint16_t brokenPixels[5];
		uint16_t outlierPixels[5];  
} paramsMLX90640;
    
int MLX90640_DumpEE(uint8_t slaveAddr, uint16_t *eeData);
int MLX90640_GetFrameData(uint8_t slaveAddr, uint16_t *frameData);
int MLX90640_ExtractParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
float MLX90640_GetVdd(uint16_t *frameData, const paramsMLX90640 *params);
float MLX90640_GetTa(uint16_t *frameData, const paramsMLX90640 *params);
void MLX90640_GetImage(uint16_t *frameData, const paramsMLX90640 *params, float *result);
void MLX90640_CalculateTo(uint16_t *frameData, const paramsMLX90640 *params, float emissivity, float tr, float *result);
int MLX90640_SetResolution(uint8_t slaveAddr, uint8_t resolution);
int MLX90640_GetCurResolution(uint8_t slaveAddr);
int MLX90640_SetRefreshRate(uint8_t slaveAddr, uint8_t refreshRate);   
int MLX90640_GetRefreshRate(uint8_t slaveAddr);  
int MLX90640_GetSubPageNumber(uint16_t *frameData);
int MLX90640_GetCurMode(uint8_t slaveAddr); 
int MLX90640_SetInterleavedMode(uint8_t slaveAddr);
int MLX90640_SetChessMode(uint8_t slaveAddr);


#define  Rate2HZ   0x02
#define  Rate4HZ   0x03
#define  Rate8HZ   0x04
#define  Rate16HZ  0x05
#define  Rate32HZ  0x06

#define  MLX_I2C_ADDR 0x33<<1
#define	 RefreshRate Rate8HZ 

#define  TA_SHIFT 8 //Default shift for MLX90640 in open air

extern paramsMLX90640 mlx90640;
extern uint16_t frame[834];
extern float Ta,tr;
extern float emissivity;
extern float mlx90640To[768];

#endif
