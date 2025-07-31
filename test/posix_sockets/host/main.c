



#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#ifdef _WIN32
 #ifndef _WIN32_WINNT
  #define _WIN32_WINNT 0x0501
 #endif
 #include <winsock2.h>
 #include <ws2tcpip.h>
#else
 #include <unistd.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <fcntl.h>
#endif




#if (__BYTE_ORDER == __BIG_ENDIAN) || __BIG_ENDIAN__
 #define htonll(x)	__uint64_identity (x)
 #define ntohll(x)	__uint64_identity (x)
#elif (__BYTE_ORDER == __LITTLE_ENDIAN) || __LITTLE_ENDIAN__
 #define htonll(x)	__bswap_64 (x)
 #define ntohll(x)	__bswap_64 (x)
#endif


#ifndef INVALID_SOCKET
 #define INVALID_SOCKET -1
#endif


#ifdef _WIN32
typedef int socklen_t;
#else
typedef int SOCKET;
#endif




void socketInit(void){

#ifdef _WIN32
	WSADATA wsa_data;
	if( WSAStartup(MAKEWORD(1,1), &wsa_data) != 0){
		fprintf(stderr,"winsock init bad\n");
		exit(0);
	}
#endif
}


void socketQuit(void){

#ifdef _WIN32
	WSACleanup();
#endif
}


void socketClose(int socket){

#ifdef _WIN32
	shutdown(socket,SD_BOTH);
	closesocket(socket);
#else
	shutdown(socket,SHUT_RDWR);
	close(socket);
#endif
}




void socketSetNonblock(int fd){

	int status;
#ifdef _WIN32
	DWORD nonblock = 1;
#endif


#ifdef _WIN32
	status = ioctlsocket(fd,FIONBIO,&nonblock);
#else
	status = fcntl(fd,F_SETFL,O_NONBLOCK,1);
#endif
	if (status != 0) {
		fprintf(stderr,"nonblock set bad\n");
		exit(0);
	}
}




void printAddr4(struct sockaddr_in* addr,const char* msg){

	char buff[3*4+4] = {0};


	inet_ntop(AF_INET,&(addr->sin_addr),buff,sizeof(buff));
	printf("%s, %d, %s\n",
			buff,
			ntohs(addr->sin_port),
			msg);
}


void printAddr6(struct sockaddr_in6* addr,const char* msg){

	char buff[4*8+8] = {0};


	inet_ntop(AF_INET6,&(addr->sin6_addr),buff,sizeof(buff));
	printf("%s, %d, %s\n",
			buff,
			ntohs(addr->sin6_port),
			msg);
}




void serverSocket(void){

	int status;
	SOCKET socketfd;
	struct sockaddr_in6 hostAddr = {0}, clientAddr = {0}, inboxAddr = {0};
	socklen_t addrsize = sizeof(struct sockaddr_in6);
	unsigned char databuffer[508] = {0};


	socketfd = socket(PF_INET6,SOCK_DGRAM,IPPROTO_UDP);
	if (socketfd == INVALID_SOCKET) { 
		fprintf(stderr,"socket creation bad\n");
		exit(0);
	}

	socketSetNonblock(socketfd);


	hostAddr.sin6_family = AF_INET6;
	hostAddr.sin6_addr = in6addr_any;
	hostAddr.sin6_port = htons((unsigned short)20000);
	status = bind(socketfd,(struct sockaddr*)&hostAddr,sizeof(hostAddr));
	if (status != 0) {
		fprintf(stderr,"socket bind bad\n");
		exit(0);
	}


	{unsigned int i;
	for(i = 0;i<10;i++){
		status = recvfrom(socketfd,databuffer,sizeof(databuffer),0,
				(struct sockaddr*)&inboxAddr,&addrsize);
		if (status > 0) {
			break;
		}
		fprintf(stderr,"%d/10 tries : no requests, "
				"trying again in %d second\n",i+1,1);
		sleep(1);
	}}


	if( !strcmp((char*)databuffer,"asdf?") ){
		printAddr6(&inboxAddr,"request accepted, client registered");
		memcpy(&clientAddr,&inboxAddr,sizeof(inboxAddr));
	}


	status = sendto(socketfd,"asdf!",sizeof("asdf!"),0,
			(struct sockaddr*)&clientAddr,sizeof(clientAddr));
	if (status != sizeof("asdf!")) {
		fprintf(stderr,"send data bad");
		perror(0);
		exit(0);
	}


	socketClose(socketfd);
}




int main(int argc, char **argv){

	socketInit();


	serverSocket();


	socketQuit();
	return 0;
}




