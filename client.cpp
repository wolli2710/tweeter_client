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
	rc=pthread_create(&threads[t],NULL, &handleThread, (void*)t);
	//login
	login();
	//User
	//receive();
   

	do{
		conversation();
	}while(1);

pthread_exit(NULL);
}

/*
int main(){

	long rc;
	SOCKET sock;
	SOCKADDR_IN addr;
	char buffer[BUFFER_SIZE], read_buffer[BUFFER_SIZE];
	int bytes;

	rc=startWinsock();															//WSAStartup returns 0 if everything is correct

	if(rc!=0)
	{
		printf("Fehler: startWinsock, fehler code: %d\n",rc);
		return 1;
	}
	sock = socket( AF_INET, SOCK_STREAM, 0 );									//AF_Inet=IPv4, Sock_Stream = TCP Socket, 0=instead of protocol

	if(sock==INVALID_SOCKET)
	{
	  printf("Der Socket konnte nicht erstellt werden, fehler code: %d\n",WSAGetLastError());
	  return 1;
	}
	memset(&addr, 0, sizeof(SOCKADDR_IN));										//memset sets a block of memory starting by &addr to the value 0 length of SOCKADDR_IN
		addr.sin_family=AF_INET;												//IPv4
		addr.sin_port=htons(5000);												// Port 5000 in use
		addr.sin_addr.s_addr=inet_addr("127.0.0.1");							// localhost
			
	printf(" Geben Sie Ihren Usernamen ein:\n");
	gets(buffer);												
	rc = connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR));						//socket, struct of sockaddr, size of sockaddr-struct

	if(rc==SOCKET_ERROR)
	{
	  printf("Fehler: connect gescheitert, fehler code: %d\n",WSAGetLastError());
	  return 1;
	}
	else
	{
		
		bytes = send(sock, buffer, strlen(buffer), 0);							//Login...
		
	 	bytes = recv(sock, read_buffer, sizeof(read_buffer) - 1, 0);			//receives the servers welcome message
		read_buffer[bytes] = '\0';												//set ende of read_buffer 
		printf("Hallo: %s\n", read_buffer);											
		
		while(1)
		{
			printf("Geben Sie eine Pingnachricht ein oder beenden Sie mit q\n");

			gets(buffer);
			bytes = send(sock, buffer, strlen(buffer), 0);

			bytes = recv(sock, read_buffer, sizeof(read_buffer) - 1, 0);
			read_buffer[bytes] = '\0';
			printf("%s\n", read_buffer);

			if(strcmp(buffer, "q")==0||strcmp(buffer, "Q")==0) 
			{
				closesocket(sock);
				exit(0);
			}	
			else if(strcmp(buffer, "f")==0)
			{
				//funktion schreiben für send recv
			}
		}
	}
	  return 0;
	}
*/

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
	//sending();
	//receive();
}

void client::receive(){
	//long tid;
	//tid = (long)threadid;

	int bytes;
	bytes = recv(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);
	receiveBuffer[bytes] = '\0';	
	cout<<receiveBuffer<<"\n";	
	pthread_exit(NULL);
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