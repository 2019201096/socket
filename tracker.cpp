//run the program by giving port number of the peer (
//server) you want to listen on
//ie ./a.out 50000
//after that enter the port of the server you as peer client want to connect to
//hence always first start the server you want to connect in other terminal
//copy the same program in all folders(peers) if any update in one and compile in all folders
//v03----here sending chunkarray[0,2,4] and no of chunks (here 3) to the server one time,,next time changing array to [1,3,5] and receiving both in one file
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string> 
#include <iostream> 
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include<map>	
#include <arpa/inet.h>
#include <bits/stdc++.h> 
#define NUM_THREADS 15
using namespace std;
struct chunkdata{
	int *chunk;
	int port;
	//int socketcli;
	int threadno;
};

map<string,vector<string> >m1;

typedef struct portrecv
{
	vector<string> pr;
};


//vector<pair<string,int> v1(10);

int main(int argc,char *argv[])
{

		
		string p=argv[1];
		string maport;
		int port=atoi(argv[1]);

		int sockser;
	int sockfd;
//	int port=p;//*((int*)p);
	struct sockaddr_in server1,client;
	unsigned int len;
	
	if((sockser=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(1);
	}
	server1.sin_family=AF_INET;
	server1.sin_port=htons(port);
	server1.sin_addr.s_addr=INADDR_ANY;
	bzero(&server1.sin_zero,8);
	
	len=sizeof(server1);


	if(bind(sockser,(struct sockaddr*)&server1,len)==-1){
		perror("bind: ");
		exit(1);
	}

	if(listen(sockser,10)==-1){
		perror("listen: ");
		exit(1);
	}
	cout<<"I am listening on port "<<port<<endl;
	while(1)
	{
			sockfd=accept(sockser,(struct sockaddr *)&client,&len);
			cout<<"sockfd"<<sockfd<<endl;
				if(sockfd==-1)
				{
					perror("accept: "); 
					exit(1);
				}
			 while(1){
		 	
			
				int choice;
				char filename[1024]={'\0'};
				int portrecv;
				int act;
				cout<<"to accept a request enter any no."<<endl;
				cin>>act;
				recv(sockfd,&choice,sizeof(int),0);//receive choice no.
				sleep(1);
				cout<<"choice "<<choice<<endl;
				sleep(2);
				if(choice==1)
				{  //ie take file name and port no and put in map
					recv(sockfd,filename,1024,0);
					cout<<"fname"<<filename<<"yes"<<endl;
					sleep(2);
					string fname(filename);
					recv(sockfd,&portrecv,sizeof(int),0);
					cout<<"port"<<portrecv<<endl;
					// m1[fname].
					//vector<int> v;
					//v1[0]=portrecv;
					maport=to_string(portrecv);
					cout<<"maport"<<maport<<endl;
					m1[fname].push_back(maport);
					vector <string> v3=m1[fname];
					for(auto it:v3)
					{
						
						cout<<it<<"yolo ";
					}

				}
				else if(choice==2)
				{  //check for filename in map and return port no.
					recv(sockfd,filename,1024,0); //received the filename 
					//cout<<"fname"<<filename<<endl;
					string fname(filename);
					//cout<<"check scope"<<v1[0];
					cout<<"fname"<<fname<<endl;
					vector<string> v2;
					 v2=m1[fname];
					// for(auto it1=m1.begin();it1!=m1.end();it1++){
					// 	if(it1->first==fname){
					// 		v2=it1->second;
					// 		break;
					// 	}
					// }
					cout<<v2[0]<<"ch"<<endl;
					for(int i=0;i<v2.size();i++)
					{
						cout<<v2[i]<<"yol2 ";
					}

					// struct portrecv *p1;
					// p1->pr=v2;
					
					//send(sockfd,p1,sizeof(portrecv),0);
					
					
					break;
				}
				 else
				 	break;

	
			}
	close(sockfd);
	}
close(sockser);
		
return 0;

}




// //void* server(void* p){
// void server(int p){d
// 	//map<string,vector<int> >m1;
// 		int sockser;
// 	int sockfd;
// 	int port=p;//*((int*)p);
// 	struct sockaddr_in server1,client;
// 	unsigned int len;
	
// 	if((sockser=socket(AF_INET,SOCK_STREAM,0))==-1){
// 		perror("socket: ");
// 		exit(1);
// 	}
// 	server1.sin_family=AF_INET;
// 	server1.sin_port=htons(port);
// 	server1.sin_addr.s_addr=INADDR_ANY;
// 	bzero(&server1.sin_zero,8);
	
// 	len=sizeof(server1);


// 	if(bind(sockser,(struct sockaddr*)&server1,len)==-1){
// 		perror("bind: ");
// 		exit(1);
// 	}

// 	if(listen(sockser,10)==-1){
// 		perror("listen: ");
// 		exit(1);
// 	}
// 	cout<<"I am listening on port "<<port<<endl;
// 	while(1)
// 	{
// 			sockfd=accept(sockser,(struct sockaddr *)&client,&len);
// 			cout<<"sockfd"<<sockfd<<endl;
// 				if(sockfd==-1){
// 					perror("accept: "); 
// 					exit(1);
// 				}
// 			// while(1){
		 	
			
// 				int choice;
// 				char filename[1024]={'\0'};
// 				int portrecv;
// 				int act;
// 				cout<<"to accept a request enter any no."<<endl;
// 				cin>>act;
// 				recv(sockfd,&choice,sizeof(int),0);//receive choice no.
// 				sleep(1);
// 				cout<<"choice "<<choice<<endl;
// 				sleep(2);
// 				if(choice==1){  //ie take file name and port no and put in map
// 					recv(sockfd,filename,1024,0);
// 					cout<<"fname"<<filename<<"yes"<<endl;
// 					sleep(2);
// 					string fname(filename);
// 					recv(sockfd,&portrecv,sizeof(int),0);
// 					cout<<"port"<<portrecv<<endl;
// 					m1[fname].push_back(portrecv);
// 					vector<int> v1;
// 					v1=m1[fname];
// 					for(auto i:v1)}
// 					{
// 						cout<<i<<"yolo ";
// 					}

// 				}
// 				else if(choice==2){  //check for filename in map and return port no.
// 					recv(sockfd,filename,1024,0); //received the filename 
// 					//cout<<"fname"<<filename<<endl;
// 					string fname(filename);
// 					cout<<"fname"<<fname<<endl;
// 					vector<int> v2;
// 					v2=m1[fname];
					
// 					{
// 						cout<<"he"<<v2[0]<<" ";
// 					}
// 					send(sockfd,&v2,v2.size()*sizeof(int),0);
					
					
// 					//break;
// 				}
// 				// else
// 				// 	break;

	
// 			//}
// 	close(sockfd);
// 	}
// close(sockser);
// }