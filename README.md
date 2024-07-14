## sg90.c

首先这是一个sg90的驱动程序

#### 部署以及学习流程

要控制舵机，首先就是输出pwm波，而如何配置pwm波的参数，是这个东西的一个难点，然后这时候也可以学习一下单片机的时钟系统


这张图很好地展示了f103c8t6的时钟树，从左到右解释一下。首先是HSI和HSE，分别是mcu内部提供的时钟源为8mhz，但是精度较差，还有外部的晶振提供的时钟源，精度较好，之后会经过预分频器，可以直接输出到sysclk，但是这样能输出的频率就比较低，不过我们这时候也可以选择先输入到pll锁相环中，这里有一个倍频器，可以在这里将前两个时钟源较低频率的时钟信号进行倍频处理，就能输出72mhz的最好性能，在sysclk之后还有一个分频器才会输出到单片机中的hclk。

hclk相当于这个时钟树的一个核心，承上启下，把时钟信号承接到各种外设和芯片的内核之中，在输出到各种外设的时候，除了内核/内存/DMA之外，基本都需要经过预分频，然后选择性倍频才能接上外设。再查看自己想要操作的那个外设的时钟频率的时候，首先要看这个外设所挂载在哪一条总线上。

#### 设置过程

例如我想要启用f103的tim1的channel1，查看芯片手册


可以看到tim1的clk在apb2总线上，并且在它之前有一个倍频器，可以选择1倍或者两倍，不过我们肯定要最高的频率，就选一倍，那么tim1的频率就是72mhz，这就是它的主频

之后还要配置一下这个timer1，首先要配置一下timer的输出模式，我们使用的是pwm模式，就直接设置就行，还有勾选内部时钟源。之后就是arr，预分频，有一个公式


然后我们控制舵机一般输出的是50hz的pwm波，所以我们这样算50hz=72000000/(ARR+1)/PRE+1

这样我们就能输出一个50hz的pwm波，然后就在软件中设置占空比，实质上就是调整比较值pulse。

这个pulse的范围是0-ARR+1，我设置的ARR为399，pre为3599，所以我可以调整的compare为0-400

之后就是换算角度和占空比的关系以实现一些现实一点的功能，这个比较简单，可以直接在代码中看到。
