TARGET  := sddp_nuvo_app
  
#compile and lib parameter
#CROSS_COMPILE	:=arm-none-linux-gnueabi-
#ARCH 	:= arm
#ROOT	:= /home/tangbin/my-imx6/rootfs-linux-3.0.5-qt4/
CXX 	:= g++
LIBS    := -lzmq -lpthread -ljsoncpp -lcanlib -lm
LDFLAGS := -L/usr/local/lib/ -L/usr/lib/
DEFINES := -D_REENTRANT
INCLUDE := -I/usr/local/include/ -I../lib/include/ -I/usr/include/
#CFLAGS  := -Wall -Wextra -Werror -O2 $(DEFINES) $(INCLUDE)
CFLAGS  := $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS)

#source file
SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

ifeq ($(SDDP_DEBUG_ON),1)
	SDDP_XTRA_CFLAGS_DEBUG= -D_DEBUG=1 -DDEBUG=1
	IS_DEBUG=DEBUG: $(SDDP_XTRA_CFLAGS_DEBUG)
	CFLAGS += $(SDDP_XTRA_CFLAGS_DEBUG)
else
	SDDP_XTRA_CFLAGS_DEBUG= -D_DEBUG=0 -DDEBUG=0
	IS_DEBUG=RELEASE
	CFLAGS += $(SDDP_XTRA_CFLAGS_DEBUG)
endif

.PHONY : objs clean

all : $(TARGET)
	@echo --------------------------------------------------------------------
	@echo "BUILD FOR [$(IS_DEBUG)] DONE"
	@echo --------------------------------------------------------------------

objs : $(OBJS)

clean :
	rm -fr *.o
	rm -fr $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
