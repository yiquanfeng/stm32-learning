//
// Created by yiquanfeng on 24-7-15.
//

#include "sg90.h"

#include "tim.h"

//我的舵机旋转角度大于180，所以某些参数可能和其他人的不一样，这里会写明白
//
void sg90_move(double degree)
{
   HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
   int compare = 0;
   __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,degree);
}
