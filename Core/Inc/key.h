//
// Created by jkhu29 on 2021/7/8.
//

#ifndef DDS_KEY_H
#define DDS_KEY_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include <string.h>

uint16_t KEY_SCAN(void);
uint16_t KEY_ROW_SCAN(void);
void HW_KEY_FUNCTION(void);

#define KEY_CLO0_OUT_LOW  HAL_GPIO_WritePin(GPIOA,KEY_col0_Pin,GPIO_PIN_RESET)
#define KEY_CLO1_OUT_LOW  HAL_GPIO_WritePin(GPIOA,KEY_col1_Pin,GPIO_PIN_RESET)
#define KEY_CLO2_OUT_LOW  HAL_GPIO_WritePin(GPIOA,KEY_col2_Pin,GPIO_PIN_RESET)
#define KEY_CLO3_OUT_LOW  HAL_GPIO_WritePin(GPIOA,KEY_col3_Pin,GPIO_PIN_RESET)

#define KEY_CLO0_OUT_HIGH  HAL_GPIO_WritePin(GPIOA,KEY_col0_Pin,GPIO_PIN_SET)
#define KEY_CLO1_OUT_HIGH  HAL_GPIO_WritePin(GPIOA,KEY_col1_Pin,GPIO_PIN_SET)
#define KEY_CLO2_OUT_HIGH  HAL_GPIO_WritePin(GPIOA,KEY_col2_Pin,GPIO_PIN_SET)
#define KEY_CLO3_OUT_HIGH  HAL_GPIO_WritePin(GPIOA,KEY_col3_Pin,GPIO_PIN_SET)

#endif //DDS_KEY_H
