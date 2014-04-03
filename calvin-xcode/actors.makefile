all: Example__m1.so Example__m2.so Example__m3.so Example__m4.so accumulate.so timed_counter.so

clean:
	@rm -f *.o *.so

%.so : %.c
	$(CC) -I$(SRCROOT)/.. -g -Wall -fPIC -flat_namespace -bundle -undefined suppress -o $@ $<
