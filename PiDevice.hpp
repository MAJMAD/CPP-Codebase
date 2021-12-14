//Jacob Mader, 12/13/2021
//Developed for the purpose of supporting operation of PI Devices via C++ in environments where the typical PI DLLs are not available
//Linux/ARM devices especially will require access to this source code as the uncompiled source code is unavailable at this time
#pragma once
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

using namespace std;

namespace pi
{

	class PiDevice{
		
		public:
		//Class Attributes
			//Device Attributes
			vector<vector<char>> Attributes;
			vector<vector<char>> Methods;
			vector<char> DeviceFamily;
			vector<char> ConnectionStatus;
			vector<char> ConnectionType;
			vector<char> Axes;
			vector<char> CurrentPosition;
			vector<char> MaxPosition;
			vector<char> MinPosition;
			vector<char> CurrentVelocity;
			vector<char> MaxVelocity;
			vector<char> MinVelocity;
			vector<char> CurrentAcceleration;
			vector<char> MaxAcceleration;
			vector<char> MinAcceleration;
			vector<char> CurrentDeceleration;
			vector<char> MaxDeceleration;
			vector<char> MinDeceleration;
			vector<char> IsMoving;
			vector<char> IsMacroRunning;
			vector<char> TravelRange;
			vector<char> LoadCapacity;
			vector<char> Mass;
			vector<char> Load;
			vector<char> LengthUnit;
			vector<char> MinimumIncrementalMotion;
			
			//Connectivity Attrbutes
			int socket_desc;
			struct sockaddr_in server;
			char *message , server_reply[2000];
			
		//Class Methods
		
			//User Methods
			void connectPI();
			void sendPI();
			void receivePI();
			
			//Connection Methods
			//void connectTCPIP();
			//void connectRS232();
			//void connectUSB();
			//void connectSPI();
			//void connectPCI();
			//todo
			
			//GCS Methods
			
			//Motion Methods
			void MOV();
			void MVR();
			
			//Setup Methods
			void SVO();
			void FRF();
			
			//Macro Methods
			//todo
			
			//Query Methods
			void TMX();
			void TMN();
			void POS();
			void SPA();
			void IDN();
			
			//Support Methods
			void HLP();
			void HPA();
			void MAN();
		
};
}
