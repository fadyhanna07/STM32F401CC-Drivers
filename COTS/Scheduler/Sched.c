/*******************************************/
/*Sched.c
Author :FADY
 Date:2023-03-24 */ 
/*******************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SYSTIC_int.h"
#include "sched.h"
#include "Sched_Cfg.h"

#define Period_time    5
/*********************************  types  *******************************************************************************/
static void SchedCBF (void);
static void Sched (void);
static u8 Sched_flag=0;
typedef struct 
{
    Task_Info_t * Task_Info ;
    u32 Remaining;
}Tasks_t;

Tasks_t Tasks [Tasks_Number];

/******************************************  Functions Implementation  ************************************************************/
void Sched_init(void)
{
    SysTick_CFG_ClockSource();
    SysTick_EnableException();
    SysTick_SetPeriod_ms(Period_time);
    SysTick_Setcbf(SchedCBF);
    for(u16 idx=0 ; idx<Tasks_Number; idx++)
    {
        Tasks[idx].Task_Info = &Tasks_Info[idx];
        Tasks[idx].Remaining = Tasks_Info[idx].Start_Delay;
    }
}
void Sched_start(void)
{
    SysTick_Start();
    while (1)
    {
        if(Sched_flag == 1)
        {
            Sched();
            Sched_flag = 0;
        }
    }
    
}
/******************************************  Static Functions   ************************************************************/
static void SchedCBF (void){
    Sched_flag = 1;
}
static void Sched (void)
{
    for(u16 idx=0 ; idx<Tasks_Number; idx++)
    {
        if(Tasks[idx].Remaining == 0){
        Tasks[idx].Task_Info->runnable();
        Tasks[idx].Remaining = Tasks[idx].Task_Info->Period;
        }
        Tasks[idx].Remaining -= Period_time;
    }

}
