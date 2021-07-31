CFLAGS = -g -no-pie -Wl,-rpath,../glibc,--dynamic-linker=../glibc/ld.so.2
TARGETS = a.out

a.out: main.c
	gcc $< $(CFLAGS) -o $@

clean:
	rm $(TARGETS)
