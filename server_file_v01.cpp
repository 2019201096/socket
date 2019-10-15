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
	int sockser;
	int sockfd;
	struct sockaddr_in server1,client;
	unsigned int len;
	
	if((sockser=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(1);
	}
	server1.sin_family=AF_INET;
	server1.sin_port=htons(50000);
	server1.sin_addr.s_addr=INADDR_ANY;
	bzero(&server1.sin_zero,8);
	
	len=sizeof(server1);
	// if(connect(socksv,(struct sockaddr*)&server,len)==-1)
	// {
	// 	perror("connect: ");
	//  	exit(1);	
	// }
	// FILE *fp=fopen("gitpwd","r");
	// fseek(fp,0,SEEK_END);
	// int size=ftell(fp);
	// rewind(fp);
	// //send(socksv,&size,sizeof(gitpwd),0);
	// char Buffer[256];
	// while((n=fread(Buffer,sizeof(char),256,fp))>0 && size>0){
	// 	send(socksv,Buffer,n,0);
	// 	memset(Buffer,'\0',256);
	// 	size=size-n;
	// }

	// fclose(fp);
	// close(socksv);

	if(bind(sockser,(struct sockaddr*)&server1,len)==-1){
		perror("bind: ");
		exit(1);
	}

	if(listen(sockser,10)==-1){
		perror("listen: ");
		exit(1);
	}
	// int  count;
	while(1){
 	sockfd=accept(sockser,(struct sockaddr *)&client,&len);
		if(sockfd==-1){
			perror("accept: "); 
			exit(1);
		}

			FILE *fp=fopen("gitpwd","rb");
	fseek(fp,0,SEEK_END);
	int size=ftell(fp);
	//cout<<size;
	rewind(fp);
	//fseek(fp,0,SEEK_SET);
	send(sockfd,&size,sizeof(int),0);
	char Buffer[256];
	int n;
	while((n=fread(Buffer,sizeof(char),256,fp))>0 && size>0){
		//cout<<n;
		send(sockfd,Buffer,n,0);
		//memset(Buffer,'\0',256);
		size=size-n;
	}
	
	close(sockfd);
	fclose(fp);
}
close(sockser);
//*********************************************************
		// FILE *fp=fopen("newf","ab");

		// char Buffer[256];
		// int file_size;
		// memset(Buffer,0,256);
		// recv(sockfd,&file_size,sizeof(int),0);
		// cout<<file_size<<"\n ";
		// int n;
		// while ((n=recv(sockfd,Buffer,25,0))>0 && file_size>0){
		// 	fwrite(Buffer,sizeof(char),n,fp);
		// 	//memset(Buffer,'\0',25);
		// 	file_size=file_size-n;
		// }
		// close(sockfd);
		// close(sockser);
		// fclose(fp);
//******************************************************************
	// 	count=send(sockcli,str,strlen(str),0);
	// 	cout<<"sent "<<count<<" bytes to "<<inet_ntoa(client.sin_addr)<<endl;
	// 	close(sockcli);
	// }

}