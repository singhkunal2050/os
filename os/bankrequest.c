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
	int request[MXSZ];			// request 
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
	int flag=0;

	while(countdown){

		for (int i = 0; i < pcount; ++i){
			flag=0;
			for (int j = 0; j < acount; ++j){
				if(P[i].need[j]<=work[j] && finish[i]!=1){
					flag++;
					if(flag==acount)
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

int request(){
	int k;
	printf("Enter which Process is requesting:: \n");
	scanf("%d",&k);
	printf("Enter the request for \n");
	for (int i = 0; i < acount; ++i){
		printf("Resource %d::"  ,i+1);
		scanf("%d",&P[k].request[i]);
	}

	printf("request for p%d\n",k);
	for (int i = 0; i < acount; ++i)
		printf("%d\t",P[k].request[i]);

	for (int i = 0; i < acount; ++i){
		if(P[k].request[i]>P[k].need[i] || P[k].request[i]>work[i]){
			printf("Comparing (%d>%d) (%d>%d)\n",P[k].request[i],P[k].need[i],P[k].request[i],work[i]);
			printf("\nThe request can not be fulfilled\n");
			return 0;		// abort
		}
	}

	// update need work and alloc for process k
	for (int i = 0; i < acount; ++i){
		P[k].alloc[i]=P[k].alloc[i]+P[k].request[i];
		work[i]=work[i]-P[k].request[i];
		P[k].need[i]=P[k].max[i]-P[k].alloc[i];				// need = need = req
	}
	return 1;

}


int main(int argc, char const *argv[])
{
	//system("clear");
	accept();
	if(request())			// if request is fulfilled then checkSS
		checkSS();
	else
		printf("\nThere is no SafeSequence\n");

	return 0;
}