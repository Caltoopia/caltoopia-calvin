REAL_NAME=calvin
OBJECTS=actors-registry.o actors-network.o \
	actors-rts.o actors-parser.o actors-teleport.o actors-debug.o \
        art_Sink_bin.o art_Sink_txt.o art_Sink_real.o \
	art_Source_bin.o art_Source_txt.o art_Source_real.o

# set up linker flags Linux
ifeq ($(shell uname -s),Linux)
  LDFLAGS += -rdynamic $(shell sdl-config --libs)
  OBJECTS += display-sdl.o display.o art_Display_yuv.o
  CFLAGS += $(shell sdl-config --cflags) -DCALVIN_DISPLAY_SUPPORT
endif
# set up linker flags Mac OS X
ifeq ($(shell uname -s),Darwin)
  LDFLAGS += -rdynamic
  OBJECTS += display-file.o display.o art_Display_yuv.o
  CFLAGS += -DCALVIN_DISPLAY_SUPPORT
endif

all: $(REAL_NAME)

$(REAL_NAME): $(OBJECTS)
	$(CC) -o $@ $^ -ldl -lpthread $(LDFLAGS)

$(OBJECTS) : %.o : %.c
	$(CC) -c -Wall $(CFLAGS) -g -o $@ $<

clean:
	@rm -f *.o *.so $(REAL_NAME)


# Rule for compiling actors for dynamic loading

# location of makefile (crude, but it seems to work)
MAKEFILE_PATH = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
CALVIN_HOME = $(shell dirname $(MAKEFILE_PATH))

%.so : %.c
	$(CC) -I$(CALVIN_HOME) -Wall -fPIC -shared -Wl,-soname,$@ -o $@ $<

%.bundle : %.c
	$(CC) -I$(CALVIN_HOME) -std=c99 -Wall -Wno-parentheses-equality -fPIC -flat_namespace -bundle -undefined suppress -o $@ $<

.INTERMEDIATE: $(OBJECTS)