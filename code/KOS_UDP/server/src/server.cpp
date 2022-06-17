#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#define MSG_SIZE        2
#define CLIENT_PORT            1106
#define MAX_RETRIES 3


int main(int argc, const char *argv[])
{

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    char data[MSG_SIZE] = {'0', '1'};
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CLIENT_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //wait until client started
    sleep(5);
    
    std::cerr << "Server has started!" << std::endl;
    
    for(int i = 0; i < MAX_RETRIES; i++)
    {
    	std::cerr << "Server sent data!" << std::endl;
    	sendto(sock, data, sizeof(data), 0, (struct sockaddr*)&addr, sizeof(addr));
    	sleep(2);
    }
	
	close(sock);
	delete[] data;
	
    return EXIT_SUCCESS;
}
