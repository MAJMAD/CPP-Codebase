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

using namespace std;

class PIDevice{
	
	public:
	//Class Attributes
		//Device Attributes
		//vector<string> Attributes;
		//vector<string> Methods;
		vector<char> DeviceFamily;
		string ConnectionStatus;
		string ConnectionType;
		string LastCommand;
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
		char *message , server_reply[10000];
		
	//Class Methods
	
		//User Methods
		int connectPI(){
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
		};
			
		int sendPI(string GCSCommand){
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
		};
		
		int sendrPI(string GCSCommand){
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
		};
		
		//Connection Methods
		//void connectTCPIP();
		//void connectRS232();
		//void connectUSB();
		//void connectSPI();
		//void connectPCI();
		//todo
		
		//GCS Methods
		
		//Motion Methods
		int MOV(PIDevice pidevice, string axes, double* targets){
			stringstream strm;
			strm << "MOV ";
			for(int i = 0; i < axes.length(); i+=2){
				strm << axes[i] << " " << targets[i/2];
				if (i < axes.length() - 1){
					strm << " ";
				}
			}
			strm << "\n";
			string s = strm.str();
			char* command = new char[s.length() + 1];
			strcpy(command, s.c_str());
			//Send some data
			pidevice.message = command;
			cout << pidevice.message << endl;
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			delete [] command;
			return 0;
			};
			
		int qMOV(PIDevice pidevice, string axes, double *targets){
			stringstream strm;
			strm << "MOV? ";
			for(int i = 0; i < axes.length(); i+=2){
				strm << axes[i];
				if (i < axes.length() - 2){
					strm << " ";
				}
			}
			strm << "\n";
			string s = strm.str();
			char* command = new char[s.length() + 1];
			strcpy(command, s.c_str());
			//Send some data
			pidevice.message = command;
			cout << pidevice.message << endl;
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 2000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);
			delete [] command;
			return 0;
			};
			
		int MVR(PIDevice pidevice, string axes, double* targets){
			stringstream strm;
			strm << "MVR ";
			for(int i = 0; i < axes.length(); i+=2){
				strm << axes[i] << " " << targets[i/2];
				if (i < axes.length() - 1){
					strm << " ";
				}
			}
			strm << "\n";
			string s = strm.str();
			char* command = new char[s.length() + 1];
			strcpy(command, s.c_str());
			//Send some data
			pidevice.message = command;
			cout << pidevice.message << endl;
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			delete [] command;
			return 0;
			};
		
		//Setup Methods
		int SVO(PIDevice pidevice, string szAxes, string pbValueArray){
			stringstream strm;
			strm << "SVO ";
			for(int i = 0; i < szAxes.length(); i+=2){
				strm << szAxes[i] << " " << pbValueArray[i];
				if (i < szAxes.length() - 2){
					strm << " ";
				}
			}
			strm << "\n";
			string s = strm.str();
			char* command = new char[s.length() + 1];
			strcpy(command, s.c_str());
			//Send some data
			pidevice.message = command;
			cout << pidevice.message << endl;
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			/*//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 2000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);*/
			delete [] command;
			return 0;
			};
			
		int qSVO(PIDevice pidevice, string szAxes, int *pbValueArray){
			stringstream strm;
			strm << "SVO? ";
			for(int i = 0; i < szAxes.length(); i+=2){
				strm << szAxes[i];
				if (i < szAxes.length() - 2){
					strm << " ";
				}
			}
			strm << "\n";
			string s = strm.str();
			char* command = new char[s.length() + 1];
			strcpy(command, s.c_str());
			//Send some data
			pidevice.message = command;
			cout << pidevice.message << endl;
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 2000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);
			delete [] command;
			return 0;
			};
		void FRF();
		
		//Macro Methods
		//todo
		
		//Query Methods
		void TMX();
		void TMN();
		
		
		int qPOS(PIDevice pidevice){
			//Send some data
			pidevice.message = (char*)"POS?\n";
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 2000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);
			return 0;
		};
		
		
		/*void SPA(){
			//Send some data
			pidevice.message = (char*)"SPA\n";
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 2000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);
			return 0;
		};
		todo
		*/
		
		void qIDN(){
			//Send some data
			pidevice.message = (char*)"*IDN?\n";
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 2000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);
			return 0;
		};
		
		//Support Methods
		int qHPA(PIDevice pidevice){
			//Send some data
			pidevice.message = (char*)"HPA?\n";
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 40000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);
			return 0;
		};

		int qHLP(PIDevice pidevice){
			//Send some data
			pidevice.message = (char*)"HLP?\n";
			if( send(pidevice.socket_desc , pidevice.message , strlen(pidevice.message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}
			puts("Data Sent\n");
			//Receive a reply from the server
			cout << pidevice.server_reply << endl;
			
			if( recv(pidevice.socket_desc, pidevice.server_reply , 40000 , 0) < 0)
			{
				puts("recv failed");
				puts(pidevice.server_reply);
			}
			puts("Reply received\n");
			puts(pidevice.server_reply);
			return 0;
		};
		void MAN();
};
