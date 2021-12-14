//Jacob Mader, 12/13/2021
//Developed for the purpose of supporting operation of PI Devices via C++ in environments where the typical PI DLLs are not available
//Linux/ARM devices especially will require access to this source code as the uncompiled source code is unavailable at this time
#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<netdb.h> // hostent
#include<unistd.h> // close()
#include<iostream> //cin
#include<string>
#include<cstring>
#include<sstream>
#include<cmath>
#include<vector>
#include<thread>
#include "PiDevice.hpp"

using namespace std;


int PIDevice::connectPI(){
			//Create socket
			socket_desc = socket(AF_INET , SOCK_STREAM , 0);
			if (socket_desc == -1)
			{
				printf("Could not create socket");
			}
			server.sin_addr.s_addr = inet_addr("169.254.7.154");
			server.sin_family = AF_INET;
			server.sin_port = htons( 50000 );
			//Connect to remote server
			if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
			{
				puts("connect error");
				return 1;
			}
			puts("Connected\n");
			ConnectionStatus = "Connected";
			ConnectionType = "TCPIP";
			return 0;
}
			
int PIDevice::sendPI(string GCSCommand){
			stringstream strm;
			strm << GCSCommand;
			strm << "\n";
			string s = strm.str();
			char* command = new char[s.length() + 1];
			strcpy(command, s.c_str());
			//Send some data
			message = command;
			cout << message << endl;
			if( send(socket_desc , message , strlen(message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			delete [] command;
			LastCommand = GCSCommand;
			return 0;
}
		
int PIDevice::sendrPI(string GCSCommand){
			stringstream strm;
			strm << GCSCommand;
			strm << "\n";
			string s = strm.str();
			char* command = new char[s.length() + 1];
			strcpy(command, s.c_str());
			//Send some data
			message = command;
			if( send(socket_desc , message , strlen(message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << server_reply << endl;
			if( recv(socket_desc, server_reply , 2000 , 0) < 0)
			{
				puts("recv failed");
				puts(server_reply);
			}
			puts("Reply received\n");
			puts(server_reply);
			delete [] command;
			LastCommand = GCSCommand;
			return 0;
}
