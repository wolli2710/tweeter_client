#include "client.h"					


void *handleThread(void *arg);

client::client()
{
}

client::~client()
{

}

void client::run(){

#ifdef WIN32
    startWinSock();
#endif

    clientSocket = socket( AF_INET, SOCK_STREAM, 0 );

    if(clientSocket == INVALID_SOCKET){
        error("Socket U fail");
        exit(1);
    }
