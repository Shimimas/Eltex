CFLAGS = -lrt -pthread

.PHONY: clean

all: client server

client: client.c
	$(CC) client.c -o client $(CFLAGS)

server: server.c
	$(CC) server.c -o server $(CFLAGS)

clean:
	rm server client