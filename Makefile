PROGRAM = calvin
SOURCES = $(wildcard *.c)
DISPLAY_SOURCES = $(wildcard display-*.c)
SOURCES := $(filter-out $(DISPLAY_SOURCES), $(SOURCES))

CFLAGS = -pg -g -Wall -DCALVIN_DISPLAY_SUPPORT -std=c99

LDFLAGS := -rdynamic -ldl -pthread -pg

# set up linux specifics
ifeq ($(shell uname -s),Linux)

ifeq ($(shell uname -m),armv6l)
  # Raspberries
  SOURCES += display-null.c
  LDFLAGS += -lm
  CFLAGS += -ggdb -pedantic
else
  # Other
  LDFLAGS += $(shell sdl-config --libs) -lm
  SOURCES += display-sdl.c
  CFLAGS += $(shell sdl-config --cflags) -ggdb -pedantic
endif
endif

# set up Mac OS X specifics
ifeq ($(shell uname -s),Darwin)
  LDFLAGS +=
  SOURCES += display-file.c
  CFLAGS += 
endif

OBJECTS = $(SOURCES:.c=.o)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJECTS) : %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o *.so $(PROGRAM)


# Rule for compiling actors for dynamic loading

# location of makefile (crude, but it seems to work)
MAKEFILE_PATH = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
CALVIN_HOME = $(shell dirname $(MAKEFILE_PATH))

%.so : %.c
	$(CC) -I$(CALVIN_HOME) -std=c99 -Wall -g -ggdb -fPIC -shared -Wl,-soname,$@ -o $@ $<

%.bundle : %.c
	$(CC) -I$(CALVIN_HOME) -std=c99 -Wall -g -Wno-parentheses-equality -fPIC -flat_namespace -bundle -undefined suppress -o $@ $<
    

.INTERMEDIATE: $(OBJECTS)

