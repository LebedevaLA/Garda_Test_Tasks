#include <iostream>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

using namespace std;

void* clientHandler (void* lpParam)
{
    intptr_t clientSock = (intptr_t)lpParam;
    char buffer[1024];
    int DataLength;
    string data;
    string message;
    for(;;)
    {
        DataLength = recv(clientSock, buffer, 1024, 0);
        if (DataLength == 0 || DataLength == -1) {
            cout << "Client disconnected." << endl;
            close(clientSock);
            return 0; 
        }
        string data = string(buffer, DataLength);;
        string message ="server echo: "+ data + '\n';
        cout << "Message get and send: " << message << endl;
        send(clientSock, message.c_str(), message.length(), 0);
    }
    return 0; 
}


int main() {
    int listensocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listensocket == -1) {
        cout << "Can't create a socket" << endl;
        return 1;
    }
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(81);

    bind(listensocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(listensocket, 10);

    cout<<"Server had started"<<endl;

    pthread_t clientThread;
    for(;;){
        struct sockaddr clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int socketforclient = accept(listensocket,&clientAddr, &clientLen);
        if (socketforclient == -1)
        {
            cout<<"Can't accept a client connection"<<endl;
        }
        pthread_create(&clientThread, NULL, clientHandler, (void*)socketforclient); // Создание потока для обработки клиента
        
    }
    return 0;
}


