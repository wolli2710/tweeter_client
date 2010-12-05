#ifndef CLIENT_H
#define CLIENT_H

#define BUFFER_SIZE 300
#define WIN32 
#define PORT 5000
#define NUM_THREADS     5

/*
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
#include <pthread.h>
#pragma comment(lib, "pthreadVC2.lib")
#include <string.h>
#include <iostream>*/
#include "includes.h"


//#include "message.h"
//#include "timestamp.h"

using namespace std;

class client
{
    public:
        client();
        ~client();
        bool connection(int port, const char* address);
        void closeClient();
        const char* client::receive(bool* successful);
        bool sending(const char* sendBuf);
        bool run();
        bool startWinSock();
        void error(string string);
        const char* getError();
        
        static void* handleThread(void *arg);    
    protected:
    private:
      
        SOCKADDR_IN addr;
        long t;
        int clientSocket;
        bool closeConnection;
        char receiveBuffer[BUFFER_SIZE];
        char sendBuffer[BUFFER_SIZE];
        char errorMessage[50];
};

#endif 
