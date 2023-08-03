bin := n2
obj := n2.o functions.o
src := n2.c functions.c
hdr := functions.h

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)