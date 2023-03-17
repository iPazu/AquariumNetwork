default:

	gcc -o udp_server udp_server.c
	gcc -o udp_client udp_client.c
	gcc -o tcp_server tcp_server.c
	gcc -o tcp_client tcp_client.c

clean:
	rm -v udp_server udp_client tcp_server tcp_client
