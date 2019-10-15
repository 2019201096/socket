#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream> 
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;
int main(){
	int sockfd;
	int sockcli;
	struct sockaddr_in server,client;
	unsigned int len;
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(1);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(50002);
	server.sin_addr.s_addr=INADDR_ANY;
	//inet_addr("127.0.0.1");
	bzero(&server.sin_zero,8);
	
	len=sizeof(server);
	if(connect(sockfd,(struct sockaddr*)&server,len)==-1)
	{
		perror("connect: ");
	 	exit(1);	
	}

	FILE *fp=fopen("newf","ab");

		char Buffer[256];
		int file_size;
		memset(Buffer,0,256);
		recv(sockfd,&file_size,sizeof(int),0);
		cout<<file_size<<"\n ";
		int n;
		while ((n=recv(sockfd,Buffer,25,0))>0 && file_size>0){
			fwrite(Buffer,sizeof(char),n,fp);
			//memset(Buffer,'\0',25);
			file_size=file_size-n;
		}
		close(sockfd);
		//close(sockser);
		fclose(fp);

	//*******************************************************
	// FILE *fp=fopen("gitpwd","rb");
	// fseek(fp,0,SEEK_END);
	// int size=ftell(fp);
	// cout<<size;
	// rewind(fp);
	// //fseek(fp,0,SEEK_SET);
	// send(sockfd,&size,sizeof(int),0);
	// char Buffer[25];
	// int n;
	// while((n=fread(Buffer,sizeof(char),25,fp))>0 && size>0){
	// 	//cout<<n;
	// 	send(sockfd,Buffer,n,0);
	// 	//memset(Buffer,'\0',256);
	// 	size=size-n;
	// }

	// fclose(fp);
	// close(sockfd);
//***********************************************************************
	// if(bind(socksv,(struct sockaddr*)&server,len)==-1){
	// 	perror("bind: ");
	// 	exit(1);
	// }

	// if(listen(socksv,10)==-1){
	// 	perror("listen: ");
	// 	exit(1);
	// }
	// int  count;
	// while(1){
	// 	sockcli=accept(socksv,(struct sockaddr *)&client,&len);
	// 	if(sockcli==-1){
	// 		perror("accept: ");
	// 		exit(1);
	// 	}

	// 	count=send(sockcli,str,strlen(str),0);
	// 	cout<<"sent "<<count<<" bytes to "<<inet_ntoa(client.sin_addr)<<endl;
	// 	close(sockcli);
	// }

}