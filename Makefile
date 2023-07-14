target = test


INCLUDE         := -I. \
                -I../opencv-3.4.7-mac/mpeg/include \
                -I../opencv-3.4.7-mac/mpeg/include/opencv 

LIBS            := \
                -L../opencv-3.4.7-mac/mpeg/lib \
                -lopencv_core -lopencv_imgproc  -lopencv_video  -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio \
                -L../opencv-3.4.7-mac/mpeg/3rdparty/lib \
                -lIlmImf    -llibjasper -llibjpeg-turbo     -llibtiff   -lzlib -llibpng -llibwebp -llibprotobuf  \
                -lstdc++  -L/usr/local/opt/ffmpeg@4/lib \
                -lavcodec -lavfilter -lavformat -lavresample -lavutil -lswscale \
                -framework IOKit -framework Foundation -framework Cocoa -framework AVFoundation -framework CoreMedia -framework CoreVideo \
				
				
CROSS_COMPILE ?= 

CC  = $(CROSS_COMPILE)gcc
#CXX = $(CROSS_COMPILE)g++
#CXX = $(CROSS_COMPILE)clang++
CXX = $(CROSS_COMPILE)clang
AR  = $(CROSS_COMPILE)ar


SRC_DIR = .

# ok for c/c++
SRC =  $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*.cpp)
SRC += $(wildcard $(SRC_DIR1)/*.c $(SRC_DIR1)/*.cpp)
SRC += $(wildcard $(SRC_DIR2)/*.c $(SRC_DIR2)/*.cpp)
SRC += $(wildcard $(SRC_DIR3)/*.c $(SRC_DIR3)/*.cpp)
SRC +=  $(wildcard $(SRC_DIR4)/*.c $(SRC_DIR4)/*.cpp)
SRC +=  $(wildcard $(SRC_DIR5)/*.c $(SRC_DIR5)/*.cpp)
SRC +=  $(wildcard $(SRC_DIR6)/*.c $(SRC_DIR6)/*.cpp)
SRC +=  $(wildcard $(SRC_DIR7)/*.c $(SRC_DIR7)/*.cpp)
SRC +=  $(wildcard $(SRC_DIR8)/*.c $(SRC_DIR8)/*.cpp)
SRC +=  $(wildcard $(SRC_DIR9)/*.c $(SRC_DIR9)/*.cpp)
SRC +=  $(wildcard $(SRC_DIR10)/*.c $(SRC_DIR10)/*.cpp)

#SRC += colorDetect.cpp

OBJECTDIR = obj
SRCOBJS = $(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(SRC))) 
OBJ = $(patsubst %,$(OBJECTDIR)/%,$(SRCOBJS))

 
#compile and lib parameter
#编译参数
LDFLAGS		:=
DEFINES		:= -DMACOS 
CFLAGS		:= -O3 -Wall -v -g $(DEFINES) $(INCLUDE)  
#-O3
CFLAGS		+= --std=c++11
CXXFLAGS	:= $(CFLAGS) -DHAVE_CONFIG_H
DYNC_FLAGS      := -fpic -shared
ARFLAGS         := -cr
LDFLAGS 	+= $(LIBS) 



ifeq ($(V),1)
Q=
NQ=true
else
Q=
NQ=echo
endif

###############################################################################


all: $(target)

$(target): $(OBJ)

ifeq ($(suffix $(target)), .so)
	@$(NQ) "Generating dynamic lib file..." $(notdir $(target))
	$(Q)$(CXX) $(CFLAGS) $^ -o $(target) $(LDFLAGS) $(DYNC_FLAGS)
else ifeq ($(suffix $(target)), .a)
	@$(NQ) "Generating static lib file..." $(notdir $(target))
	$(Q)$(AR) $(ARFLAGS) -o $(target) $^
else
	@$(NQ) "Generating executable file..." $(notdir $(target))
	$(Q)$(CXX) $(CFLAGS) $^ -o $(target) $(LDFLAGS)
endif

# make all .c or .cpp
$(OBJECTDIR)/%.o: %.c
	@[ ! -d $(dir $@) ] & mkdir -p $(dir $@)
	@$(NQ) "Compiling: " $(addsuffix .c, $(basename $(notdir $@)))
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTDIR)/%.o: %.cpp
	@[ ! -d $(dir $@) ] & mkdir -p $(dir $@)
	@$(NQ) "Compiling: " $(addsuffix .cpp, $(basename $(notdir $@)))
	$(Q)$(CXX) $(CFLAGS) -c $< -o $@

clean:
	@$(NQ) "Cleaning..."
	$(Q)$(RM) $(target)
	@find . -iname '*.o' -o -iname '*.bak' -o -iname '*.d' | xargs rm -f

.PHONY: all clean
 
