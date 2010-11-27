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

	memset(&addr, 0, sizeof(SOCKADDR_IN));										
	addr.sin_family=AF_INET;												
	addr.sin_port=htons(5000);												
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");							

	connection();
	//receive right connected
	int rc;
	t=0;
	receive();
	//login
	login();
	//User
	//receive();
   
//rc=pthread_create(&threads[t],NULL, &handleThread, (void*)t);
	do{
		conversation();
	}while(1);

pthread_exit(NULL);
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
	cout<<"Geben Sie Ihren Usernamen ein:\n";
	cin>>sendBuffer;
	rc = send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
	if(rc==SOCKET_ERROR){
		error("login failed\n");
	}	
}	

void client::closeClient(){
	closesocket(clientSocket);
	exit(0);
}

void client::conversation(){
	sending();
	receive();
}

void client::receive(){
	//long tid;
	//tid = (long)threadid;

	int bytes;
	bytes = recv(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);
	receiveBuffer[bytes] = '\0';	
	cout<<receiveBuffer<<"\n";	
	//pthread_exit(NULL);
}

void client::sending(char* sendBuf){
	int rc;
    rc = send(clientSocket, sendBuf, sizeof(sendBuf), 0);
	if(rc==SOCKET_ERROR){
		error("Sending failed");
	}
	else{
        cout << sendBuf << " (gesendet)\n";
	}
}

void *handleThread(void *arg){

	//while oder ähnliches
	static_cast<client*>(arg)->receive();


	return (NULL);
}