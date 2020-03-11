#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MXSZ 10

void calculateAvg();

typedef struct process{
	char pname[10];
	int atime,btime,tatime,stime,ftime,wtime;
	int finish;
}PROCESS;

PROCESS P[MXSZ];
int c;				//process count
int sysclock=0;
float atat,awt;			//averages

void readProcess(){
	int i;
	int a,b;
	printf("ENTER THE PCount\n");
	scanf("%d",&c);

	srand(time(0));
	for(i=0;i<c;i++){
		printf("Enter %d Pname \n",i+1 );
		scanf("%s",P[i].pname);
		a=rand()%10;
		b=rand()%5;
		P[i].atime=a;
		P[i].btime=b+1;			// avoid 0 btime 
		P[i].finish=0;				// unfinished

		// printf("Enter %d atime \n",i+1 );
		// scanf("%d",&P[i].atime);
		
		// printf("Enter %d btime \n",i+1 );
		// scanf("%d",&P[i].btime);

		//now calculate start tat and waiting with sort f

		// printf("%s PROCESS :: Atime :: %d btime :: %d\n",P[i].pname,P[i].atime,P[i].btime);
	}
}


void display(){
	int i=0;
	printf("------------------------------------------------------\n");
	printf("PROCESS  Atime  Btime STime Ftime WTIme Tatime::\n");
	while(i<c){
		printf("%s\t %d\t%d\t %d\t%d\t %d\t%d\n",P[i].pname,P[i].atime,P[i].btime,P[i].stime,P[i].ftime,P[i].wtime,P[i].tatime);
		i++;
	}
	printf("------------------------------------------------------\n");
	
}

void sortf(){
	int i,j;
	PROCESS t;
	
	for(i=0;i<c;i++){
		for(j=0;j<c-i-1;j++){
			if(P[j+1].atime<P[j].atime){
				t= P[j];
				P[j]=P[j+1];
				P[j+1]=t;
			}
		}	
	}
}


// void sorts(){

// 	PROCESS t;
// 	int i,j;

// 	sortf();

// 	for(i=0;i<c;i++){
// 		for(j=0;j<c-i-1;j++){
// 			if(P[j].atime==P[j+1].atime)
// 				if(P[j].btime>P[j+1].btime){
// 				t= P[j];
// 				P[j]=P[j+1];
// 				P[j+1]=t;
// 			}
// 		}
// 	}
// }


void executeFCFS(){
	sortf();
	sysclock=0;
	int wflag=0;

	printf("------------------------------------------------------\n");
	for (int i = 0; i < c; i++){
		wflag=0;
		if(P[i].atime>sysclock){
			while(P[i].atime>sysclock){
				sysclock++;
				//printf("waiting 1cy\t");
				wflag=1;
			}
		}
		P[i].stime=sysclock;
		sysclock=sysclock+P[i].btime;
		P[i].ftime=sysclock;
		P[i].wtime=P[i].stime-P[i].atime;
		P[i].tatime=P[i].ftime-P[i].atime;	

		if(wflag)
			printf("IDLE");
		printf("(%d| %s |%d) ",P[i].stime,P[i].pname,P[i].ftime);
		// printf("Process : %s ST=>%d FT=>%d\t",P[i].pname,P[i].stime,P[i].ftime);
	}
	printf("\n--------------------------------------------------------\n");
	calculateAvg();
}


int getProcess(){
	int k=0,min=999;
	int index=-1;

	while(k<c){
		if(P[k].atime<=sysclock){
			if(P[k].finish==0 && min>P[k].btime){
				min=P[k].btime;
				index=k;
			}
		}
		k++;
	}
	return index;
}

void executeSJF(){
	sortf();
	sysclock=0;
	int wflag=0;
	int i=0;

	if(P[0].atime>sysclock){
		printf("IDLE\n");
		while(P[0].atime>sysclock)
			sysclock++;
	}

	printf("------------------------------------------------------\n");
	for (int j = 0; j < c; j++){
		wflag=0;
		i=getProcess();
		// printf("inside sjf :: i :: %d\n",i);
		if(i==-1){
			while(getProcess()==-1)
				sysclock++;
		}
		else{
			P[i].stime=sysclock;
			sysclock=sysclock+P[i].btime;
			P[i].ftime=sysclock;
			P[i].wtime=P[i].stime-P[i].atime;
			P[i].tatime=P[i].ftime-P[i].atime;	
			P[i].finish=1;

			if(wflag)
				printf("IDLE");
			printf("(%d| %s |%d) ",P[j].stime,P[j].pname,P[j].ftime);

			// printf("Process : %s ST=>%d FT=>%d\t",P[i].pname,P[i].stime,P[i].ftime);
		}

	}
	printf("\n--------------------------------------------------------\n");
	calculateAvg();
}


void calculateAvg(){
	int i,sum=0,sum2=0;
	for (i = 0; i < c; ++i){
		sum=sum+P[i].wtime;
		sum2=sum2+P[i].tatime;
	}

	awt=sum/(float)c;
	atat=sum2/(float)c;

	printf("\nAverage WT =>%f\nAverage TAT =>%f\n",awt,atat);
}



/*
void printChart(){
	printf("\n-------------------------------------------\n");
	for (int i = 0; i < c; i++){
		if(P[i].stime>P[i].atime)
			printf("IDLE");
		printf("(%d| %s |%d) ",P[i].stime,P[i].pname,P[i].ftime);
	}	
	printf("\n-------------------------------------------\n");

}
*/