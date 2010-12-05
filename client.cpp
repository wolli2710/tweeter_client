#include "client.h"					


client::client()
{
}

client::~client()
{
}   

bool client::run(){
    startWinSock();
    clientSocket = socket( AF_INET, SOCK_STREAM, 0 );
    if(clientSocket < 0){
        error("Socket U fail");
        return false;
    }
    return true;
}

const char* client::getError(){
    return errorMessage;
}

bool client::startWinSock()									
{
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(wVersionRequested, &wsaData)!=0){
        memcpy(errorMessage, "WinSocket not available", sizeof("WinSocket not available"));
        return false;
    }
    return true;
}

//Error Handling function which prints a individual string with the errormessage
void client::error(string string){
        sprintf(errorMessage, "%s Error:%d\n",string, WSAGetLastError());
}

bool client::connection(int port, const char* address){
    memset(&addr, 0, sizeof(SOCKADDR_IN));										
    addr.sin_family=AF_INET;												
    addr.sin_port=htons(port);												
    addr.sin_addr.s_addr=inet_addr(address);							

    int rc;											
    rc = connect(clientSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));						

    if(rc < 0)
    {
        error("Connect failed");
        return false;
    }
    else
    {
        cout<<"Connected...\n";
        return true;
    }
}

void client::closeClient(){
    closesocket(clientSocket);
}

const char* client::receive(bool* successful){
    int bytes;
    bytes = recv(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);
    if(bytes < 0) {
        error("Receive failed");
        *successful = false;
    }
    else *successful = true;
    receiveBuffer[bytes] = '\0';	

    return receiveBuffer;
}

bool client::sending(const char* sendBuf){
    int rc;
    memcpy(sendBuffer, sendBuf, strlen(sendBuf));
    sendBuffer[strlen(sendBuf)] = '\0';
    
    rc = send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
    if(rc < 0){
        error("Sending failed");
        return false;
    }
    else{
        return true;        
    }
}