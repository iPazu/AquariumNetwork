default:
	gcc -o tcp_server tcp_server.c -lpthread
	gcc -o tcp_client tcp_client.c

back:
	gcc -c tcp_server.c -o tcp_server.o 
	gcc -c display_aquarium.c -o display_aquarium.o
	gcc -c fish.c -o fish.o
	gcc -c aquarium.c -o aquarium.o
	gcc main.c tcp_server.o display_aquarium.o fish.o aquarium.o -o tcp_server -lpthread

clean:
	rm -v tcp_server tcp_client *.o
