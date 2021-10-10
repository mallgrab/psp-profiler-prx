TARGET = profiler
OBJS = profiler.o

INCDIR =
CFLAGS = -O2 -g -G0 -Wall

CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS=exports.exp

USE_KERNEL_LIBC=1
USE_KERNEL_LIBS=1

# LIBDIR = ./
LDFLAGS = -nostartfiles
LIBS = -lpspkernel

PSP_FW_VERSION=660

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

EXTRA_TARGETS = profilerLib.S

profilerLib.S : $(PRX_EXPORTS)
	psp-build-exports --build-stubs $(PRX_EXPORTS)
