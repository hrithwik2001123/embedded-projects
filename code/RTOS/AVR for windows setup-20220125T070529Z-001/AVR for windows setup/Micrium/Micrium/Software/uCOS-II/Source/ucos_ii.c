/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                          (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File : uCOS_II.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#define  OS_GLOBALS                           /* Declare GLOBAL variables                              */
#include "includes.h"


#define  OS_MASTER_FILE                       /* Prevent the following files from including includes.h */
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_core.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_flag.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_mbox.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_mem.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_mutex.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_q.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_sem.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_task.c"
#include "C:\Micrium\Micrium\software\ucos-ii\source\os_time.c"

//#include <os_core.c>
//#include <os_flag.c>
//#include <os_mbox.c>
//#include <os_mem.c>
//#include <os_mutex.c>
//#include <os_q.c>
//#include <os_sem.c>
//#include <os_task.c>
//#include <os_time.c>
