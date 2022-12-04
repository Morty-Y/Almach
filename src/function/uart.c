#include <stdio.h>
#include "uart.h"

static int uart_Pack(plan_TypeDef plan, unsigned char* buf)
{
    return 0;
}

int uart_Send(plan_TypeDef plan)
{
    unsigned char tx[3] = { 0 };
    unsigned char rx = 0;
    uart_Pack(plan, tx);

    printf("plan.man.az = %d\n", plan.man.az);
    printf("plan.man.zd = %d\n", plan.man.zd);
    return 0;
}