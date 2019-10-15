//creating multi threading on server side
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream> 
#include <unistd.h>
#include <arpa/inet.h>
#define NUM_THREADS 15
using namespace std;
struct taskids{
	int socketfd;
	int threadid;
};
void* handlethreadrequest(void* tasks1){
			FILE *fp=fopen("gitpwd","rb");
			struct taskids *tasks=(struct taskids*)tasks1;
			int sockfd=tasks->socketfd;
			int threadid=tasks->threadid;
			//cout<<"thread id: "<<threadid<<endl;
			// fseek(fp,0,SEEK_END);
			// int size=ftell(fp);
					//cout<<size;
					//rewind(fp);
					//fseek(fp,0,SEEK_SET);
					//send(sockfd,&size,sizeof(int),0);


				unsigned int x=threadid*50;
					fseek(fp,x,SEEK_SET);
					// if(fseek(fp,0,x)!=0){
					// 	return NULL;//fseek return non zero value on failure
					// }		
					//cout<<"x val "<<x<<endl;	
					int size=50;
					char Buffer[50];
					int n;
					//char y=(char)x;
					//send to send the fp position
					//char *buf=(char*)&x;
				//	int insize=sizeof(x);
				//	int sent=0;
					//int buf[1]={x};
					//int y=buf+sent;
					cout<<x<<endl;
					if((n=fread(Buffer,sizeof(char),50,fp))>0 && size>0)
					{
						//cout<<n;
						send(sockfd,&x,sizeof(x),0);
						send(sockfd,Buffer,n,0);
						//memset(Buffer,'\0',256);
						size=size-n;
					}
			
	
	
	//close(sockfd);
	fclose(fp);
	return NULL;
}
void server(){
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
					fclose(fp);
	pthread_t threads[NUM_THREADS]; 
	struct taskids *task[NUM_THREADS];
	//int *taskids[NUM_THREADS];
	for(int t=0;t<NUM_THREADS;t++) 
	{
		task[t]=(taskids*)malloc(sizeof(taskids));
	task[t]->threadid = t;
	task[t]->socketfd =sockfd;
	//(int *) malloc(sizeof(int));
//	*taskids[t] = t;
	//printf("Creating thread %d\n", t);
	int rc = pthread_create(&threads[t], NULL, handlethreadrequest,(void *) task[t] );
	if (rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc); 
		exit(-1);
		}
	}
	for(int t=0;t<NUM_THREADS;t++) 
	{
		pthread_join(threads[t],NULL);
	}
	close(sockfd);
	
}
close(sockser);
}

int main(){

server();

}
