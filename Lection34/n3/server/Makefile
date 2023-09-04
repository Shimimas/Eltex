bin := main
obj := main.o server.o list.o msgq_data.o
src := main.c server.c ../general/list.c ../general/msgq_data.c
hdr := server.h ../general/list.h ../general/msgq_data.h

CFLAGS := -lncurses -lpanel -pthread -lrt

.PHONY: clean

$(bin): $(obj)
	$(CC) $(obj) -o $(bin) $(CFLAGS)

$(obj): $(src)
	$(CC) $(src) -c

$(obj): $(hdr)

clean:
	rm $(bin) $(obj)