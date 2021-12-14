//Jacob Mader, 12/13/2021
//Developed for the purpose of supporting operation of PI Devices via C++ in environments where the typical PI DLLs are not available
//Linux/ARM devices especially will require access to this source code as the uncompiled source code is unavailable at this time
#pragma once
#include<stdio.h>
#include<string.h>	
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<netdb.h> 
#include<unistd.h>
#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<cmath>
#include<vector>
#include<thread>

using namespace std;

class PIDevice{
		
		public:
		//Class Attributes
			//Device Attributes
			//vector<vector<char>> Attributes;
			//vector<vector<char>> Methods;
			//vector<char> DeviceFamily;
			string ConnectionStatus;
			string ConnectionType;
			string LastCommand;
			/*vector<char> Axes;
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
			vector<char> MinimumIncrementalMotion;*/
			
			//Connectivity Attrbutes
			int socket_desc;
			struct sockaddr_in server;
			char *message , server_reply[10000];
			
		//Class Methods
		
			//User Methods
			int connectPI();
			int sendPI(string GCSCommand);
			int sendrPI(string GCSCommand);
			
			/*
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
			void MAN();*/
		
};
