#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream> 
#include <unistd.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <vector>
#include <map>
#define NUM_THREADS 15
using namespace std;

int main()
{	
	int parr[]={0,0,0,0,0,0};
	vector<vector<int> > v1{{1,0,0,0,0,1},{1,0,1,1,1,1},{1,0,0,1,1,1}};
	// v1[3][3]=
	//suppose 3 ports have a file
	//ask for bit arr from each port in for loop...then for each array set priority inside bit array
	//let no of chunks in file be 3(size of file/chunk size)..below for loop for i =0 to 2(total )
	for(int i=0;i<v1.size();i++){
		int k=0;
		for(int j=0;j<v1[i].size();j++){
			if (v1[i][j]==0)
				continue;
			else
			{
				v1[i][j]+=k;
				k=v1[i][j];

			}

			
		}
	}
	/////*************************include***********************************************
	// for(int i=0;i<3;i++){
	// 	for(int j=0;j<v1[0].size();j++)
	// 		cout<<v1[i][j]<<" ";
	// 	cout<<endl;
	// }
	/////////**********************till here***********************************************
	int p=-1;
	
	
	// multimap<int,int> m1;

	// for(int i=4;i>=0;i--) // (no of chunks from last to firt)
	// {  ///column last to first
	// 	int min=9999;
		
	// 	for(int j=0;j<=2;j++)//row first to last(no of ports)
	// 	{
	// 		if(v1[j][i]<=min && v1[j][i]>0) //choose the min in that column(which is highest priority except when it is 0..meaning chunk unavailable)
	// 		{
	// 			if(v1[j][i]==min) //if that column has same priority level(at min no.), then choose the port(i.e j value) with least no.(higer prioity)
	// 			{
	// 				if(parr[j]>parr[p]) //if current port(j value) has higher no means lower priority then continue...else it will update port (p) to current j value
	// 					continue;
	// 			}
	// 		min=v1[j][i];
	// 		p=j;  //port at jth pos in array of ports
	// 		}
	// 	}

	// 	//m1[p].emplace_back(i);//port p will fetch chunk i
	// 	m1.insert(pair<int,int>(p,i));//port p will fetch chunk i
	// 	parr[p]++; //increase number to decrease priority of that port where to fetch from(such that if next time there is a clash in if condn then choose the port which did not send earlier) 
	// }

	// for (auto itr = m1.begin(); itr != m1.end(); ++itr) 
 //    { 
 //        cout << '\t' << itr->first 
 //             << '\t' << itr->second << '\n'; 
 //    } 


     map<int,vector<int> >m1;
     for(int i=v1[0].size()-1;i>=0;i--) // (no of chunks from last to firt)
	{  ///column last to first
		int min=9999;
		int flag=0; ///to check that chunk shud be present ie. v1[i][j]>0,then set flag =1
		for(int j=0;j<v1.size();j++)//row first to last(no of ports)
		{
			if(v1[j][i]<=min && v1[j][i]>0) //choose the min in that column(which is highest priority except when it is 0..meaning chunk unavailable)
			{
				flag=1;
				if(v1[j][i]==min) //if that column has same priority level(at min no.), then choose the port(i.e j value) with least no.(higer prioity)
				{
					if(parr[j]>parr[p]) //if current port(j value) has higher no means lower priority then continue...else it will update port (p) to current j value
						continue;
				}
			min=v1[j][i];
			p=j;  //port at jth pos in array of ports
			}
		}

		//m1[p].emplace_back(i);//port p will fetch chunk i
		//m1.insert(pair<int,int>(p,i));//port p will fetch chunk i
		if(flag==1) ///if  flag =0 means that chunk(column no) is not present in any port(row) since that column is all zero(so dont fetch that chunk)
		{
			m1[p].push_back(i);
		 		parr[p]++;
		} //increase number to decrease priority of that port where to fetch from(such that if next time there is a clash in if condn then choose the port which did not send earlier) 
	}
	vector<int> v;
	v=m1[1];
	for(auto i : v)
		cout<<i<<endl;
	// for (auto itr = m1.begin(); itr != m1.end(); ++itr) 
 //    { 
 //        cout << '\t' << itr->first 
 //             << '\t';
 //         vector<int> v;
	// 	 v=itr->second;
	// 	for(auto i : v)
	// 	cout<<i<<" ";
	// cout<<endl;
 //    } 






	return 0;

}
