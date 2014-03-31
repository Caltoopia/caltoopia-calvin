all: Example__m1.so Example__m2.so Example__m3.so Example__m4.so accumulate.so

clean:
	@rm -f *.o *.so

%.so : %.c
	$(CC) -I$(SRCROOT)/.. -Wall -fPIC -flat_namespace -bundle -undefined suppress -o $@ $<
