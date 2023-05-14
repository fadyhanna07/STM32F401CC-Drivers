/*******************************************/
/*Sched_CFG.c
Author :FADY
 Date:2023-03-24*/
/*******************************************/
#include "STD_TYPES.h"
#include "Sched_Cfg.h"
extern void Task1(void);
extern void Task2(void);
extern void Task3(void);

const Task_Info_t Tasks_Info[Tasks_Number]={
    [0]={
        .name = "led toggle 500ms",
        .Period = 500,
        .runnable = Task1,
        .Start_Delay = 0, 
    },
    [1]={
         .name = "led toggle 1000ms",
        .Period = 1000,
        .runnable = Task2,
        .Start_Delay = 0, 
    },
    [2]={
         .name = "led toggle 1500ms",
        .Period = 1500,
        .runnable = Task3,
        .Start_Delay = 0, 
    },
};


