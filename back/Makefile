default:

	gcc -o tcp_server tcp_server.c
	gcc -o tcp_client tcp_client.c

back:
	gcc -c tcp_server.c -o tcp_server.o
	gcc -c aquarium.c -o aquarium.o
	gcc main.c tcp_server.o aquarium.o -o tcp_server

clean:
	rm -v tcp_server tcp_client *.o
