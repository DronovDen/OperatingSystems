all: server client
.PHONY: all
server: server.c
	cc server.c -lsocket -o server
client: client.c
	cc client.c -lsocket -o client
clean:
	rm -rf server client




