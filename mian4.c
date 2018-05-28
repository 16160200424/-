# include"LPC11XX.H"
unsigned int status;
//led 初始化
void LedInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
	LPC_IOCON->PIO2_0 &=~0x07;
	LPC_IOCON->PIO2_0 |=~0x00;
	LPC_IOCON->PIO2_1 &=~0x07;
	LPC_IOCON->PIO2_1 |=~0x00;	
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);	
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<6);
  LPC_GPIO2->DIR |=(1<<0);
  LPC_GPIO2->DATA |=(1<<0);
  LPC_GPIO2->DIR |=(1<<1);
  LPC_GPIO2->DATA |=(1<<1);
}
//初始化系统街拍定时器
void SysTickInit(void)
{
SysTick->CTRL &=~(1<<2);
SysTick->	LOAD=12499999;
SysTick->VAL=0;
SysTick->CTRL|=((1<<1)|(1<<0));
NVIC_EnableIRQ(SysTick_IRQn);	
}
//系统街拍定时器中断服务函数
void SysTick_Handler(void)
{
status=LPC_GPIO2->DATA;
	LPC_GPIO2->DATA=~status;
}
//主函数
int main(void)
{
LedInit();
	SysTickInit();
	while(1)
	{}
}