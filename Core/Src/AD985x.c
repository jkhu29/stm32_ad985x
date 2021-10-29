//
// Created by jkhu29 on 2021/7/9.
//

#include "ad985X.h"
#include "retarget.h"

//**函数名：void AD985x_Init(void)
//**函数功能：AD985x初始化
//**输出参数：无
//**输出参数：无
//**返回值：无
//**该函数并入MX_GPIO_Init

//**函数名：void AD985x_Reset_Serial(void)
//**函数功能：AD985x复位
//**输出参数：无
//**输出参数：无
//**返回值：无
void AD985x_Reset_Serail(void)
{
  HAL_GPIO_WritePin(GPIOC, AD985x_RESET_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, AD985x_RESET_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, AD985x_RESET_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOC, AD985x_W_CLK_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, AD985x_W_CLK_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, AD985x_W_CLK_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOC, AD985x_FQ_UD_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, AD985x_FQ_UD_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, AD985x_FQ_UD_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOC, AD985x_DATA_Pin, GPIO_PIN_RESET);
  printf("reset!");
}

//**函数名：void AD985x_Set_Frequency(unsigned char W0,unsigned long Fre)
//**函数功能：AD985x设置频率
//**输出参数：W0:W0寄存器的数值(0x00)，Fre，写入的频率
//**输出参数：无
//**返回值：无
void AD985x_Set_Frequency(unsigned char W0,unsigned long Fre)
{
  unsigned char i;
  unsigned long Fre_Data;

  AD985x_Reset_Serail();     //设置频率之前 先复位IC

  Fre_Data = (4294967296/125000000)*Fre;

  HAL_GPIO_WritePin(GPIOC, AD985x_FQ_UD_Pin, GPIO_PIN_RESET);  //拉低频率、相位

  // 写入W4, W3, W2, W1四个频率寄存器
  for(i=0;i<32;i++)
  {
    HAL_GPIO_WritePin(GPIOC, AD985x_W_CLK_Pin, GPIO_PIN_RESET);
    if((Fre_Data >> i) & 0x01)
    {
      HAL_GPIO_WritePin(GPIOC, AD985x_DATA_Pin, GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOC, AD985x_DATA_Pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(GPIOC, AD985x_W_CLK_Pin, GPIO_PIN_SET);
  }

  //写W0寄存器
  for(i=0;i<8;i++)
  {
    HAL_GPIO_WritePin(GPIOC, AD985x_W_CLK_Pin, GPIO_PIN_RESET);
    if((W0>>i)&0x01)
    {
      HAL_GPIO_WritePin(GPIOC, AD985x_DATA_Pin, GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOC, AD985x_DATA_Pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(GPIOC, AD985x_W_CLK_Pin, GPIO_PIN_SET);
  }
  HAL_GPIO_WritePin(GPIOC, AD985x_FQ_UD_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, AD985x_FQ_UD_Pin, GPIO_PIN_RESET);
}
