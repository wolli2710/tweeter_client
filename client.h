#ifndef CLIENT_H
#define CLIENT_H

#define RECEIVE_BUFFER_SIZE 140
#define SEND_BUFFER_SIZE 300
#define WIN32 
#define PORT 5000

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
#include <string.h>
#endif
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
        void run();
        void startWinSock();
        void error(char* string);
	
    protected:
    private:
      
        SOCKADDR_IN addr;
       
        int clientSocket;
		bool closeConnection;
		char receiveBuffer[RECEIVE_BUFFER_SIZE];
		char sendBuffer[SEND_BUFFER_SIZE];
};

#endif 
