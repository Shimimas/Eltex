bin := main
obj := main.o functions.o
src := main.c functions.c
hdr := functions.h

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)