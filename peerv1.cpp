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
#include <string.h> 
#include <iostream> 
#include <unistd.h>
#include <cstdlib>
#include <arpa/inet.h>
#define NUM_THREADS 15
using namespace std;
// struct chunkdata{
// 	int chunk[];
// 	int totalchunk;
// };



void* server(void* p){

		int sockser;
	int sockfd;
	int port=*((int*)p);
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
	
	while(1){
 	sockfd=accept(sockser,(struct sockaddr *)&client,&len);
		if(sockfd==-1){
			perror("accept: "); 
			exit(1);
		}

  		FILE *fp=fopen("gitpwd","rb");
		fseek(fp,0,SEEK_END);
		int size=ftell(fp);
		cout<<"size 1 is"<<size<<endl;
		fseek(fp,0,SEEK_SET);
		//rewind(fp);
		send(sockfd,&size,sizeof(int),0); ////////////////////////////////////////////////////////////////////
		int count;
		recv(sockfd,&count,sizeof(int),0); //////////////////////////////////////////////////////////////////
		int chunkarr[count];
		recv(sockfd,chunkarr,sizeof(chunkarr),0); ////////////////////////////////////////
		char Buffer[256];
		int n;
		for(int i=0;i<count;i++)
		{
			int x=chunkarr[i]*50;
	  		fseek(fp, x, SEEK_SET);
	  		//int size1=ftell(fp);
	  		//cout<<"size 2is"<<size1<<endl;
			if((n=fread(Buffer,sizeof(char),50,fp))>0 )//&& size>0)
			{
				send(sockfd,Buffer,n,0);    ////////////////////////////////////////////////////////
				//size=size-n;
			}
		}	
	
	close(sockfd);
	fclose(fp);
	
	}
close(sockser);
}


void* client(void * chunkno)
{
	int sockfd;
	int sockcli;
	//int *id_ptr = (int *) threadid;
	//int taskid=*id_ptr;
	struct sockaddr_in server,client;
	unsigned int len;
	while(1)
	{
		if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
			perror("socket: ");
			exit(1);
		}
		//cout<<" thread :"<<taskid<<" socket: "<<sockfd<<endl;
		server.sin_family=AF_INET;
		
		int p;
		cout<<"enter port of the peer server you want to connect: ";
		cin>>p;
		//=50000;
		//+taskid;
		server.sin_port=htons(p);
		server.sin_addr.s_addr=INADDR_ANY;
		//inet_addr("127.0.0.1");
		bzero(&server.sin_zero,8);
		
		len=sizeof(server);
		if(connect(sockfd,(struct sockaddr*)&server,len)==-1)
		{
			perror("connect: ");
		 	exit(1);	
		}
		FILE *fp=fopen("newf","r+a");
		//FILE *fp=fopen("newf","a+");
		//int x=taskid*256;
	  //  fseek(fp, 0, x);
			char Buffer[50];
		int file_size;
		memset(Buffer,0,50);
		recv(sockfd,&file_size,sizeof(int),0);///////////////////////////////////////////////////////////
		cout<<file_size<<"\n ";
		int n;
		//adding below to receive fp
		
		// unsigned int buf=0;
		// recv(sockfd,&buf,sizeof(buf),0);
		int chunk[]={0,2,4};  //2,0
		int count=sizeof(chunk)/sizeof(chunk[0]);

		// struct chunkdata *c1=(chunkdata*)malloc(sizeof(chunkdata));
		// c1->chunk=chunk;
		//c1->totalchunk=count;
		send(sockfd,&count,sizeof(count),0);//////////////////////////////////
		send(sockfd,chunk,sizeof(chunk),0);///////////////////////////////////////////////////////////////
		for(int i=0;i<count;i++)
		{
			int x=chunk[i]*50;
	  		fseek(fp, x, SEEK_SET);
			if((n=recv(sockfd,Buffer,50,0))>0)// &&file_size>0////////////////////////////////////////////////////
				{
				fwrite(Buffer,sizeof(char),n,fp);
				}		
		}
		close(sockfd);
		fclose(fp);
	}
	
	return NULL;

}

int main(int argc,char *argv[])
{

		pthread_t t1;
		pthread_t t2;
		//string p=argv[1];
		int port=atoi(argv[1]);
		int rc1=pthread_create(&t1, NULL, server,(void *)&port);
		if (rc1)
		 {
		  printf("ERROR; return code from pthread_create() is %d\n", rc1); 
			exit(-1);
		 }

//int chunk[]={1,3,5};  //2,0
		
		// int count=sizeof(chunk)/sizeof(chunk[0]);
		// pthread_t t2[count];
		// for(int i=0;i<count;i++){
			
		// 	int *chunkno=(int*)malloc(sizeof(int));
		// 	*chunkno=chunk[i];
			//int rc2=pthread_create(t2[i], NULL,client,(void *) chunkno);
			int rc2=pthread_create(&t2, NULL,client,NULL);
			if (rc2) 
			{
			printf("ERROR; return code from pthread_create() is %d\n", rc2); 
			exit(-1);
			}
		pthread_join(t1,NULL);
		//for(int j=0;j<count;j++)
		pthread_join(t2,NULL);
return 0;

}
