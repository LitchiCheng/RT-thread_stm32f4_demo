/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     misonyo   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_spi.h>
#include "SEGGER_RTT.h"

/* defined the LED0 pin: PD14 */
#define LED0_PIN1    GET_PIN(C, 8)
#define LED0_PIN0    GET_PIN(C, 9)

static void thread_entry(void* parameter)
{
	while(1){
		rt_kprintf("RRRRRRRR\r\n");
		rt_thread_mdelay(5);			
	}
}

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN0, PIN_MODE_OUTPUT);
	rt_pin_mode(LED0_PIN1, PIN_MODE_OUTPUT);
	
	rt_thread_t thread_ptr;
    thread_ptr = rt_thread_create("thread2",
                                thread_entry, RT_NULL,
                                4096, 25, 25);
    if (thread_ptr != RT_NULL) rt_thread_startup(thread_ptr);

    while (count++)
    {
		rt_kprintf("dddddd \r\n");
        rt_pin_write(LED0_PIN1, PIN_HIGH);
		rt_pin_write(LED0_PIN0, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN1, PIN_LOW);
		rt_pin_write(LED0_PIN0, PIN_HIGH);
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}
