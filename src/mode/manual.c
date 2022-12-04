#include <stdio.h>
#include "utc.h"
#include "pid.h"
#include "uart.h"
#include "kb.h"

#define DFT_PRECISION 1000

static plan_TypeDef plan = {
    {
        .az = 0,
        .zd = 0
    },
    {
        .az = 0,
        .zd = 0
    }
};

static void instruction(void)
{
    printf("Instruction:\n");
    printf("\t[q]\tQuit\n");
    printf("\t[1]-[4]\tSwitch precision\n");
    printf("\t[i]\tZenith Distance - forward\n");
    printf("\t[k]\tZenith Distance - backward\n");
    printf("\t[j]\tAzimuth - forward\n");
    printf("\t[l]\tAzimuth - backward\n");
    printf("Default precision: %d\n", DFT_PRECISION);
}

void manual(void)
{
    int ascii = 0;
    int prec = DFT_PRECISION;
    int motor_status = 0;
    long dt = 0;
    stpvector_TypeDef plan_man = {
        .az = 0,
        .zd = 0
    };
    utc_TypeDef current, past;
    
    instruction();
    kb_Init();

    utc_Update(&past);
    while (1)
    {
        ascii = kb_Scan();
        if (ascii == 'q')
            break;
        else if (ascii == '1')
        {
            prec = 1;
            printf("Current precision: %d\n", prec);           
        }
        else if (ascii == '2')
        {
            prec = 10;
            printf("Current precision: %d\n", prec);  
        }
        else if (ascii == '3')
        {
            prec = 100;
            printf("Current precision: %d\n", prec); 
        }
        else if (ascii == '4')
        {
            prec = 1000;
            printf("Current precision: %d\n", prec); 
        }
        else if (ascii == 'i')
        {
            if(plan_man.zd == 0)
            {
                plan_man.zd += prec;
            }
        }
        else if (ascii == 'k')
        {
            if(plan_man.zd == 0)
            {
                plan_man.zd -= prec;
            }
        }
        else if (ascii == 'j')
        {
            if(plan_man.az == 0)
            {
                plan_man.az += prec;
            }
        }
        else if (ascii == 'l')
        {
            if(plan_man.az == 0)
            {
                plan_man.az -= prec;
            }
        }

        if (motor_status)
        {
            printf("Error: mstatus %d", motor_status);
            return;
        }

        utc_Update(&current);
        dt = (current.tv.tv_sec - past.tv.tv_sec) * 1000000 + (current.tv.tv_usec - past.tv.tv_usec);
        if(dt > 20000)
        {
            printf("dt = %ld\n", dt);
            plan.man = plan_man;
            motor_status = uart_Send(plan);
            past = current;
            plan_man.az = 0;
            plan_man.zd = 0;
            dt = 0;
        }
    }
    kb_Close();
}