bin := n1
obj := n1.o my_exits.o
src := n1.c my_exits.c
hdr := my_exits.h

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)
