//
// Created by jkhu29 on 2021/7/8.
//
#include "key.h"
#include "retarget.h"

uint8_t Key_row[1] = {0xff}; // 保存按键行扫描情况的状态函数

/***
 *函数名：KEY_ROW_SCAN
 *功  能：按键行扫描
 *返回值：1~4，对应1~4行按键位置
 */
uint16_t KEY_ROW_SCAN(void)
{
    //读出行扫描状态
    Key_row[0] = HAL_GPIO_ReadPin(GPIOB, KEY_row0_Pin)<<3;
    Key_row[0] = Key_row[0] | (HAL_GPIO_ReadPin(GPIOB, KEY_row1_Pin)<<2);
    Key_row[0] = Key_row[0] | (HAL_GPIO_ReadPin(GPIOB, KEY_row2_Pin)<<1);
    Key_row[0] = Key_row[0] | (HAL_GPIO_ReadPin(GPIOB, KEY_row3_Pin));

    if(Key_row[0] != 0x0f)         //行扫描有变化，判断该列有按键按下
    {
        HAL_Delay(10);                    //消抖
        if(Key_row[0] != 0x0f)
        {
            printf("Key_Row_DATA = 0x%x\r\n",Key_row[0]);
            switch(Key_row[0])
            {
                case 0x07:         //0111 判断为该列第1行的按键按下
                    return 1;
                case 0x0b:         //1011 判断为该列第2行的按键按下
                    return 2;
                case 0x0d:         //1101 判断为该列第3行的按键按下
                    return 3;
                case 0x0e:         //1110 判断为该列第4行的按键按下
                    return 4;
                default :
                    return 0;
            }
        }
        else return 0;
    }
    else return 0;
}

/***
 *函数名：KEY_SCAN
 *功  能：4*4按键扫描
 *返回值：0~16，对应16个按键
 */
uint16_t KEY_SCAN(void)
{
    uint16_t Key_Num = 0;       //1-16对应的按键数
    uint16_t key_row_num = 0;        //行扫描结果记录

    KEY_CLO0_OUT_LOW;
    if( (key_row_num=KEY_ROW_SCAN()) != 0 )
    {
        printf("Key_Row_1\r\n");
        while(KEY_ROW_SCAN() != 0);  //消抖
        Key_Num = 0 + key_row_num;
        printf("Key_Clo_1\r\n");
    }
    KEY_CLO0_OUT_HIGH;

    KEY_CLO1_OUT_LOW;
    if( (key_row_num=KEY_ROW_SCAN()) != 0 )
    {
        while(KEY_ROW_SCAN() != 0);
        Key_Num = 4 + key_row_num;
        printf("Key_Clo_2\r\n");
    }
    KEY_CLO1_OUT_HIGH;

    KEY_CLO2_OUT_LOW;
    if( (key_row_num=KEY_ROW_SCAN()) != 0 )
    {
        while(KEY_ROW_SCAN() != 0);
        Key_Num = 8 + key_row_num;
        printf("Key_Clo_3\r\n");
    }
    KEY_CLO2_OUT_HIGH;

    KEY_CLO3_OUT_LOW;
    if( (key_row_num=KEY_ROW_SCAN()) != 0 )
    {
        while(KEY_ROW_SCAN() != 0);
        Key_Num = 12 + key_row_num;
        printf("Key_Clo_4\r\n");
    }
    KEY_CLO3_OUT_HIGH;

    return Key_Num;
}

/***
 *函数名：HW_KEY_FUNCTION
 *功  能：执行按下按键后的USART输出
 *返回值：无
 */
void HW_KEY_FUNCTION(void)
{
    uint16_t key_confirm;
    key_confirm = KEY_SCAN();
//    printf("%d \r\n", key_confirm);
    if( 0 < key_confirm && key_confirm < 17 )
    {
        printf("Key_NUM = %d \r\n",key_confirm); //按下1-16个按键的操作
        printf("= = = = = = = = = = = \r\n");
    }
}
