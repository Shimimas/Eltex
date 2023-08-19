bin := main
obj := main.o client.o msgq_data.o list.o
src := main.c client.c ../general/list.c ../general/msgq_data.c
hdr := client.h ../general/list.h ../general/msgq_data.h

CFLAGS := -lncurses -lpanel

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin) $(CFLAGS)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)