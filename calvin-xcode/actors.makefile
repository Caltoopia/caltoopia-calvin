all: Example__m1.bundle Example__m2.bundle Example__m3.bundle Example__m4.bundle accumulate.bundle timed_counter.bundle

clean:
	@rm -f *.o *.bundle *.so

%.bundle : %.c
	$(CC) -I$(SRCROOT)/.. -g -Wall -fPIC -flat_namespace -bundle -undefined suppress -o $@ $<
