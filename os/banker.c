#include <stdio.h>
#include <stdlib.h>
#define MXSZ 10

void calculateNeed(); 

int acount;					// alloc per process
int pcount;					// process count
int work[MXSZ];				// avl / work
int finish[MXSZ];			// finish flag  of every process
int safesequence[MXSZ];		// safesequence => you add the processes index after its finished to ss
int safesequenceindex=0;	// for travesing ss

struct Process{
	int max[MXSZ];
	int alloc[MXSZ];
	int need[MXSZ];
};

struct Process P[MXSZ];			// array of processes

void accept(){
	printf("Enter the count of Processes\n");
	scanf("%d",&pcount);
	printf("Enter the number Alloc/Resources per Process\n");
	scanf("%d",&acount);

	printf("Enter ALlocations\n");
	for (int i = 0; i < pcount; ++i){
		printf("Process %d\n",i+1);
		for (int j = 0; j < acount; ++j){
			printf("Resources %d\t",j+1);
			scanf("%d",&P[i].alloc[j]);
		}
	}

	printf("Enter Max\n");
	for (int i = 0; i < pcount; ++i){
		printf("Process %d\n",i+1);
		for (int j = 0; j < acount; ++j){
			printf("Resources %d\t",j+1);
			scanf("%d",&P[i].max[j]);
		}
	}

	printf("Enter Work/Available\n");
	for (int i = 0; i < acount; ++i){
		scanf("%d",&work[i]);
	}

	calculateNeed();

}

void calculateNeed(){
	printf("Need Matrix\n");
	for (int i = 0; i < pcount; ++i){
		for (int j = 0; j < acount; ++j){
			P[i].need[j]=P[i].max[j]-P[i].alloc[j];			
			printf("%d\t",P[i].need[j]);
		}
		printf("\n");
	}

}

void execute(int index){
	finish[index]=1;								//set finish
	for (int i = 0; i < acount; ++i)
			work[i]=work[i]+P[index].alloc[i];		// updated work
	safesequence[safesequenceindex]=index;
	safesequenceindex++;
}

void displaySS(){
	printf("Safe sequence:: \n");
	for (int i = 0; i < pcount; ++i)
		printf("%d=>%d\t",i+1,safesequence[i]+1);		// 1 is the offset
}

void checkSS(){
	int countdown=20;					// try 20 iterations to get safe sequence
	int k;
	int cnt=0;

	while(countdown){

		for (int i = 0; i < pcount; ++i){
			cnt=0;
			for (int j = 0; j < acount; ++j){
				if(P[i].need[j]<work[j] && finish[i]!=1){
					cnt++;	
					if(cnt==acount)
						execute(i);
				}
				else{
					printf("%d is waiting ----\t",i+1);
				}
			}
		}
 
		for (k = 0; k < pcount; ++k){
			if(finish[k]!=1)
				break;
		}
		if(k==pcount){
			printf("All processes executed\n");
			displaySS();
			return;		// from while
		}
		countdown--;
	}
	printf("The sequence is not safe\n");
}

int main(int argc, char const *argv[])
{
	//system("clear");
	accept();
	checkSS();

	return 0;
}