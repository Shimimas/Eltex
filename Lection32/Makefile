bin := main
obj := main.o functions.o
src := main.c functions.c
hdr := functions.h

CFLAGS := -lncurses -lpanel

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin) $(CFLAGS)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)