bin := main
obj := main.o lifeemulation.o
src := main.c lifeemulation.c
hdr := lifeemulation.h

CFLAGS := -pthread

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin) $(CFLAGS)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)