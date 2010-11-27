#ifndef CLIENT_H
#define CLIENT_H

#define BUFFER_SIZE 300
#define WIN32 
#define PORT 5000
#define NUM_THREADS     5


#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#endif
#pragma comment(lib, "pthreadVC2.lib")
#include <pthread.h>
#include <string.h>
#include <iostream>

//#include "message.h"
//#include "timestamp.h"

using namespace std;

class client
{
    public:
        client();
        virtual ~client();
		void connection();
		void conversation();
        void closeClient();
		void login();
		void receive();
		void sending(char* sendBuf);
        void run();
        void startWinSock();
        void error(char* string);
	
    protected:
    private:
      
        SOCKADDR_IN addr;
		long t;
        int clientSocket;
		bool closeConnection;
		char receiveBuffer[BUFFER_SIZE];
		char sendBuffer[BUFFER_SIZE];

		pthread_t threads[NUM_THREADS];

};

void *thread(void* arg);

#endif 
