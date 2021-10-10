# psp-profiler-prx
Kernel module for debugging, returns profiling registers.

Move profiler.prx and profilerLib.S to your project.

In your project's Makefile include profilerLib.o to OBJS

Example:
```cpp
SceUID modid;
PspDebugProfilerRegs regs;
int ret;
int fd;

modid = sceKernelLoadModule("KernelProfiler.prx", 0, NULL);
ret = sceKernelStartModule(modid, 0, NULL, &fd, NULL);

ProfileClear();
ProfileEnable();
ProfileGetRegs(&regs);

printf("D cache miss : %10u", regs.d_miss);
```
