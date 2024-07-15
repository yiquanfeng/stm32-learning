//
// Created by yiquanfeng on 24-7-15.
//

#include "oled.h"

#include <stdatomic.h>
#define OLED_ADDRESS 0x78

void OLED_SendCmd(uint8_t cmd)
{
    uint8_t sendBuffer[2];
    sendBuffer[0] = 0x00;
    sendBuffer[1] = cmd;
    HAL_I2C_Master_Transmit(&hi2c1,OLED_ADDRESS,sendBuffer,2,HAL_MAX_DELAY);
}

void OLED_Init()
{
    OLED_SendCmd(0xAE);//关闭显示 display off

    OLED_SendCmd(0x20);//设置内存寻址模式 set memory addressing mode
    //OLED_SendCmd(0x00);//水平寻址模式horizontal addressing mode
    //OLED_SendCmd(0x01);//垂直寻址模式vertical addressing mode
    OLED_SendCmd(0x10);//页寻址模式（推荐）page addressing mode
    //OLED_SendCmd(0x11);//无效

    OLED_SendCmd(0xB0);//为页寻址模式设置开始地址，0～7 set page start address for page addressing mode
    OLED_SendCmd(0xC8);//设置输出扫描方向 set COM output scan direction
    OLED_SendCmd(0x00);//设置起始列地址 set low column address
    OLED_SendCmd(0x10);//设置结束列地址 set high column address
    OLED_SendCmd(0x40);//设置开始行地址 set start line address

    OLED_SendCmd(0x81);//设置对比度控制寄存器 set contrast control register
    OLED_SendCmd(0xFF);//亮度调节 0x00~0xFF

    OLED_SendCmd(0xA1);//设置分段重新映射 set segment re-map 0~127
    OLED_SendCmd(0xA6);//设置正常显示 set normal display
    OLED_SendCmd(0xA8);//设置多路复用率 set multiplex ratio 1～64
    OLED_SendCmd(0x3F);

    OLED_SendCmd(0xA4);//输出设置的RAM内容 output follows RAM content
    //OLED_SendCmd(0xA5);//输出忽略的RAM内容 output ignores RAM content

    OLED_SendCmd(0xD3);//设置显示偏移 set display offset
    OLED_SendCmd(0x00);//不偏移 not offset

    OLED_SendCmd(0xD5);//设置时钟分频/晶振频率 set display clock divide ratio/oscillator frequency
    OLED_SendCmd(0xF0);//设置分频率 set divide ratio

    OLED_SendCmd(0xD9);//设置放电/预充电时间 set pre-charge period
    OLED_SendCmd(0x22);
    OLED_SendCmd(0xDA);//设置引脚布局 set com pins
    OLED_SendCmd(0x12);

    OLED_SendCmd(0xDB);//设置电平 set vcomh
    OLED_SendCmd(0x20);

    OLED_SendCmd(0x8D);//设置DC-DC set DC-DC

    OLED_SendCmd(0x14);

    OLED_SendCmd(0xAF);//开启OLED turn oled panel
    OLED_SendCmd(0x8D); // 电荷泵使能
    OLED_SendCmd(0x14); // 开启电荷泵
    OLED_SendCmd(0xAF); // 点亮屏幕
}

void OLED_TEST(void)
{
    OLED_SendCmd(0xB0);
    OLED_SendCmd(0x02);
    OLED_SendCmd(0x10);

    uint8_t sendBuffer[] = {0x40,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};
    HAL_I2C_Master_Transmit(&hi2c1,OLED_ADDRESS,sendBuffer,sizeof(sendBuffer),HAL_MAX_DELAY);

}

