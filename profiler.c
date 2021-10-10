/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * profiler.c - Debug profiler functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <stdio.h>

#define PROFILER_REG_BASE 0xBC400000
#define PROFILER_REG_COUNT 21

PSP_MODULE_INFO("KernelModule", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

void ProfileEnable(void)
{
	_sw(1, PROFILER_REG_BASE);
}

void ProfileDisable(void)
{
	_sw(0, PROFILER_REG_BASE);
	asm("sync\r\n");
}

void ProfileClear(void)
{
	u32 addr;
	int i;

	addr = PROFILER_REG_BASE;
	/* Don't clear the enable register */
	for(i = 1; i < PROFILER_REG_COUNT; i++)
	{
		addr += 4;
		_sw(0, addr);
	}
}

void ProfileGetRegs(PspDebugProfilerRegs *regs)
{
	u32 *p_regs;
	u32 addr;
	int i;

	if(regs == NULL)
	{
		return;
	}

	p_regs = (u32 *) regs;

	addr = PROFILER_REG_BASE;
	for(i = 0; i < PROFILER_REG_COUNT; i++)
	{
		p_regs[i] = _lw(addr);
		addr += 4;
	}
}

#define WELCOME_MESSAGE "\n"

int module_start(SceSize args, void *argp)
{
    printf(WELCOME_MESSAGE);
	return 0;
}

int module_stop()
{
	return 0;
}

/*
void pspDebugProfilerPrint(void)
{
	PspDebugProfilerRegs regs;

	pspDebugProfilerGetRegs(&regs);

	pspDebugScreenPrintf("********** Profile ***********\n");
	pspDebugScreenPrintf("enable         : %10u\n", regs.enable);
	pspDebugScreenPrintf("systemck       : %10u [cycles]\n", regs.systemck);
	pspDebugScreenPrintf("cpu ck         : %10u [cycles]\n", regs.cpuck);
	pspDebugScreenPrintf("stall          : %10u [cycles]\n", regs.internal + regs.memory +
			regs.copz + regs.vfpu);
	pspDebugScreenPrintf("+(internal)    : %10u [cycles]\n", regs.internal);
	pspDebugScreenPrintf("+--(memory)    : %10u [cycles]\n", regs.memory);
	pspDebugScreenPrintf("+----(COPz)    : %10u [cycles]\n", regs.copz);
	pspDebugScreenPrintf("+----(VFPU)    : %10u [cycles]\n", regs.vfpu);
	pspDebugScreenPrintf("sleep          : %10u [cycles]\n", regs.sleep);
	pspDebugScreenPrintf("bus access     : %10u [cycles]\n", regs.bus_access);
	pspDebugScreenPrintf("uncached load  : %10u [times]\n", regs.uncached_load);
	pspDebugScreenPrintf("uncached store : %10u [times]\n", regs.uncached_store);
	pspDebugScreenPrintf("cached load    : %10u [times]\n", regs.cached_load);
	pspDebugScreenPrintf("cached store   : %10u [times]\n", regs.cached_store);
	pspDebugScreenPrintf("I cache miss   : %10u [times]\n", regs.i_miss);
	pspDebugScreenPrintf("D cache miss   : %10u [times]\n", regs.d_miss);
	pspDebugScreenPrintf("D cache wb     : %10u [times]\n", regs.d_writeback);
	pspDebugScreenPrintf("COP0 inst.     : %10u [inst.]\n", regs.cop0_inst);
	pspDebugScreenPrintf("FPU  inst.     : %10u [inst.]\n", regs.fpu_inst);
	pspDebugScreenPrintf("VFPU inst.     : %10u [inst.]\n", regs.vfpu_inst);
	pspDebugScreenPrintf("local bus      : %10u [cycles]\n", regs.local_bus);
}
*/
