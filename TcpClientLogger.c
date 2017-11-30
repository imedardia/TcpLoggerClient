/*
 * TCP C Logger Client: Receive Logs from running TCP Server Application
 * and display it locally on stdout
 * Can be extended to be a complete GUI Remote Logging Application
*/
#include<stdio.h>       //printf
#include<string.h>      //strlen
#include<sys/socket.h>  //socket
#include<arpa/inet.h>   //inet_addr
#include<signal.h>       //SIGINT handler
#include<unistd.h>      //close
#include<stdlib.h>      //close

#define MAX_TCP_RCV_SIZE 4096

int ClientSock;
int KeepRunning = 0;

enum TCPClientErrors
{
     CeTcpClient_Success = 0,
     CeTcpClient_SockKO,
     CeTcpClient_ConnKO,
     CeTcpClient_RecvKO,
     CeTcpClient_Args,
     CeTcpClient_MaxErr
};

void SignalHandler(int signo)
{
    if(signo == SIGINT){
        printf("Interrupt Signal catched");
        KeepRunning = 0;
    }
}

void PrintHelp()
{
    printf("RemoteTcpLogger host port\n");
}

int main(int argc , char *argv[])
{
    struct sigaction mSigAction;
    mSigAction.sa_handler = SignalHandler;
    mSigAction.sa_flags = 0;
    sigemptyset( &mSigAction.sa_mask );
    sigaction(SIGINT, &mSigAction, NULL );
    struct sockaddr_in TcpServerAddr;
    char RecvLog[MAX_TCP_RCV_SIZE] = {0};
    enum TCPClientErrors RetError = CeTcpClient_Success;
    ClientSock = -1;
    
    //Check Arguments
    if(argc != 3) {
		PrintHelp();
		return (RetError = CeTcpClient_Args);
	}

    //Create TCP socket
    ClientSock = socket(AF_INET , SOCK_STREAM , 0);
    if (ClientSock == -1) {
        printf("Could not create socket");
        RetError = CeTcpClient_SockKO; 
    }else {

	    TcpServerAddr.sin_addr.s_addr = inet_addr(argv[1]);
        TcpServerAddr.sin_family = AF_INET;
        TcpServerAddr.sin_port = htons(atoi(argv[2]));

        //Now Connect to remote TCP Server: localhost:port
        if (connect(ClientSock , (struct sockaddr *)&TcpServerAddr , sizeof(TcpServerAddr)) < 0)
        {
            perror("connect failed. Error");
            RetError = CeTcpClient_ConnKO;
        }else {
		    printf("Successfully Connected to Remote TCP Server \n");
			KeepRunning = 1;
            //keep receiving Logs from TCP server
            while(KeepRunning)
            {
                if( recv(ClientSock , RecvLog , 4096 , 0) < 0)
                {
                    printf("recv failed");
                    RetError = CeTcpClient_RecvKO;
                    break;
                }
                printf("%s",RecvLog);
            }
	    }
	}

    return RetError;
}
