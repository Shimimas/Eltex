bin := n3
obj := n3.o functions.o
src := n3.c functions.c
hdr := functions.h

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)