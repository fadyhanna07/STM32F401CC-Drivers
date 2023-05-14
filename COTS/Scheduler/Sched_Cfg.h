/*******************************************/
/*Sched_CFG.h
Author :FADY
 Date:2023-03-24*/
/*******************************************/
#ifndef _Sched_CFG_H
#define _Sched_CFG_H
/**********************************************************************/
#define Tasks_Number     3
/*********************************  types  *******************************************************************************/
typedef void (*RunnableCBF_t) (void);

typedef struct
{
    char* name;
    RunnableCBF_t runnable ;
    u32 Period;
    u32 Start_Delay;
}Task_Info_t;

extern const Task_Info_t Tasks_Info[Tasks_Number];

#endif /*Sched_CFG_H*/
