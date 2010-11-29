#include "client.h"					

//void* client::handleThread(void *arg);

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

    memset(&addr, 0, sizeof(SOCKADDR_IN));										
    addr.sin_family=AF_INET;												
    addr.sin_port=htons(5000);												
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");							

    connection();
    //receive right connected

    receive();
    //user can login, if no one else uses the same name
    login();
       
	   

	//conversation uses the methods sending and receive to handle 
	//userinput and gets massages from the server
    do{
        conversation();
    }while(1);

//pthread_exit(NULL);
}

//starts Winsock version 2.0, WSADATA is a 
//struct containing info about win socket implementation
void client::startWinSock()									
{
#ifdef WIN32
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(wVersionRequested, &wsaData)!=0){
        printf("WinSocket not available");
        exit(1);
    }
#endif
}

//Error Handling function which prints a individual string with the errormessage
void client::error(char* string){
    #ifndef WIN32
        cout << endl << perror(string) << endl;
    #else 
        cout << endl << string << " " << WSAGetLastError() << endl;
    #endif
}

void client::connection(){
    int rc;											
    rc = connect(clientSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));						

    if(rc==SOCKET_ERROR)
    {
        error("Connect failed");
        exit(1);
    }
    else
    {
        cout<<"Connected...\n";
    }	
}

void client::login(){
    int rc;
    do{
        cout<<"Geben Sie Ihren Usernamen ein:\n";
        fflush(stdin);
		fgets(sendBuffer, 140, stdin);
		size_t p=sizeof(sendBuffer);
		sendBuffer[p-1]='\0';


        rc = send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
        if(rc==SOCKET_ERROR){
            error("login failed\n");
        }
        receive();
    }while(strcmp(receiveBuffer,"Already logged in")==0);
}	

void client::closeClient(){
    closesocket(clientSocket);
    exit(0);
}

void client::conversation(){
cout<<"Geben Sie eine Message ein:\n";
        fflush(stdin);
		fgets(sendBuffer, 140, stdin);
		size_t p=sizeof(sendBuffer);
		sendBuffer[p-1]='\0';
    sending(sendBuffer);
	pthread_t pid;
	 int rc;
	 rc=pthread_create(&pid ,NULL, &client::handleThread, this);
   // receive();
}

void client::receive(){
    //long tid;
    //tid = (long)threadid;
    int bytes;
    bytes = recv(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);
    receiveBuffer[bytes] = '\0';	
    cout<<receiveBuffer<<"\n";	
}

void client::sending(char* sendBuf){
    int rc;
    memcpy(sendBuffer, sendBuf, strlen(sendBuf));
    sendBuffer[strlen(sendBuf)] = '\0';
    rc = send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
    if(rc==SOCKET_ERROR){
        error("Sending failed");
    }
    else{
        cout << sendBuf << " (gesendet)\n";
    }
}

void* client::handleThread(void *arg){
    //while oder ähnliches
    client* clientThread = static_cast<client*>(arg);
	pthread_detach(pthread_self());

    while(true){
        clientThread->receive();
    }
    return (NULL);
}
