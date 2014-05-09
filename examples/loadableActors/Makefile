ACTORS = accumulate timed_counter

ifeq ($(OS),Windows_NT)
    LIBEXT =.dll
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LIBEXT =.so
    endif
    ifeq ($(UNAME_S),Darwin)
        LIBEXT =.bundle
    endif
endif

LIBEXT ?=.so

all: $(addsuffix $(LIBEXT), $(ACTORS)) calvin.py

%.so: %.c
	make -f ../../Makefile $@

%.bundle: %.c
	make -f ../../Makefile $@

calvin.py:
	ln -sf ../../python_support/calvin.py .

clean:
	rm -f $(addsuffix $(LIBEXT), $(ACTORS))
