/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "src/platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "sleep.h"  // Include the sleep header
#include "xparameters.h"
#include "mb_interface.h"

#define GPO1 0x80010010
#define GPO2 0x80010014
#define GPO3 0x80010018
#define GPO4 0x8001001c

#define GPI1 0x80010020

#define LED_PIN GPO1
#define DFX_ICAP_GNT GPO2
#define DFX_ICAP_REL GPO3
#define DFX_ICAP_REQ GPI1

#define KEY_NEW_ADDR GPO4
#define KEY_STREAM_ID 0
#define KEY_IV_ID 1

#define DFXC_VS1_STATUS 0
#define DFXC_VS2_STATUS 1
#define DFXC_VS3_STATUS 2

#define MAX_COUNT 1000
#define BUFFER_SIZE 16

/*
 * Write 16 32-bit words as efficiently as possible.ergergerge
 */
static void inline write_key(volatile unsigned int *a)
{
    register int a0,  a1,  a2,  a3;
    register int a4,  a5,  a6,  a7;


    a3  = a[3];  a1  = a[1];  a2  = a[2];  a0  = a[0];
    a7  = a[7];  a5  = a[5];  a6  = a[6];  a4  = a[4];

    putfsl(a0,  KEY_STREAM_ID); putfsl(a1,  KEY_STREAM_ID); putfsl(a2,  KEY_STREAM_ID); putfsl(a3,  KEY_STREAM_ID);
    putfsl(a4,  KEY_STREAM_ID); putfsl(a5,  KEY_STREAM_ID); putfsl(a6,  KEY_STREAM_ID); putfsl(a7,  KEY_STREAM_ID);

}

/*
 * Write 16 32-bit words as efficiently as possible.
 */
static void inline write_IV(volatile unsigned int *a)
{
    register int a0,  a1,  a2,  a3;

    a3  = a[3];  a1  = a[1];  a2  = a[2];  a0  = a[0];

    putfsl(a0,  KEY_IV_ID); putfsl(a1,  KEY_IV_ID); putfsl(a2,  KEY_IV_ID); putfsl(a3,  KEY_IV_ID);
}

/*
 * Read 16 32-bit words as efficiently as possible.
 */
static void inline read_axis_dfxc_status(volatile unsigned int *a, uint8_t id)
{
    register int a0;

    getfsl(a0,  0);

    a[0]  = a0;
}




int main()
{
	uint8_t for_debug = 0;

	uint8_t key_debug[256/8] = {0xf1};
	uint8_t IV_debug[128/8] = {0xe2};

    uint8_t cap_req = 0;

    volatile unsigned int vs1_status[1] = {0};
    volatile unsigned int vs2_status[1] = {0};
    volatile unsigned int vs3_status[1] = {0};

	init_platform();


    Xil_Out32(DFX_ICAP_GNT, 1);
//    Xil_In32();

    print("Hello-- from World\n\r");
    while(1)
    {


    	switch(for_debug)
    	{
    	case 0:
    		write_key(key_debug);
    			break;
    	case 1:
    		write_IV(IV_debug);
    	    	break;
    	case 2:
    		Xil_Out32(KEY_NEW_ADDR, 1);
    	    	break;
    	case 3:
    		Xil_Out32(KEY_NEW_ADDR, 0);
    	    	break;
    	case 4:
    		 Xil_Out32(DFX_ICAP_GNT, 1);
    	    	break;
    	case 5:
    		 Xil_Out32(DFX_ICAP_GNT, 0);
    	    	break;
    	case 6:
    		cap_req = Xil_In32(DFX_ICAP_REQ);
    	    	break;
    	case 7:
    		read_axis_dfxc_status(vs1_status, 0);
				break;
    	case 8:
			read_axis_dfxc_status(vs2_status, 1);
				break;
    	case 9:
			read_axis_dfxc_status(vs3_status, 2);
				break;

    	default: break;
    	}

    	Xil_Out32(LED_PIN, 1);
    	usleep(50000);
    	Xil_Out32(LED_PIN, 0);
    	usleep(50000);
    }
    print("Successfully ran Hello World application");
    cleanup_platform();
    return 0;
}






