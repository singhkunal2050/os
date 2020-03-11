#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define MXSZ 10

typedef struct files{
	char fname[10];
	int start,length;
	struct files *next;
}files;

files *F=NULL;		//firs 
files *L=NULL;				//last
files *T=NULL;				// temp

long long int bitvector;				// stores the bit sequence of blocks 1|0 for free|taken
int disksize;
int useddisk=0;
int D[MXSZ];



 
files* newnode(){
	files *temp = (struct files *)malloc(sizeof(struct files));
	temp->next=NULL;
	return temp;
}

void init(){
	F=newnode();
	F->next=NULL;
	L=newnode();
	L->next=NULL;
}

void initDisk(){
	for (int i = 0; i < disksize; ++i){
		D[i]=1;			// 1=>space is free		
	}
}

void displayBitVector(){
	printf("BIT Vector\t::");
	for (int i = 0; i < disksize; ++i){
		printf(" %d ",D[i]);
	}
}

int spaceAvailable(){
	int cnt=0;
	for (int i = 0; i < disksize && D[i]==0; ++i)
		cnt++;
	// printf("Count :: %d\n",cnt);
	if(cnt==disksize)
		return 0;
	else
		return 1;
}

int getContagiousMemory(int length){
	int blockno;
	int gotmemory;

	for (int i = 0; i < disksize; ++i){
		if(D[i]==1){
			gotmemory=1;
			for (int j = 0,blockno=i; j < length; ++j){		//check for continous memory
				if(D[blockno++]==1)
					continue;
				else{
					gotmemory=0;
					break;
				}
			}
		}
		if(gotmemory){
			printf("returning %d\n",i);
			return i;
		}
	}
	return -1;
}

void allocFile(){
	char fn[10];
	int fileset=0;				// flag
	int length;
	int blockno=0;

	if(spaceAvailable()){
		do{
			printf("Enter the Fname\n");
			scanf("%s",fn);
			fileset=1;
			if(T!=NULL){
				for (T=F; T!=NULL; T=T->next){			// traverse all files to check if the file already exists
					if(strcmp(T->fname,fn)==0){
						fileset=0;
						printf("File already Exists\n");
						break;	
					}								
				}
			}
		}while(!fileset);

		printf("enter the length for allocation:\t");
		scanf("%d",&length);
		if(length<=0){
			printf("Invalid length\n");
			exit(0);
		}
		if(length>disksize-useddisk){
			printf("No Disk Space Available\n");
			exit(0);
		}	
		blockno=getContagiousMemory(length); 
		if(blockno==-1){
			printf("\nERROR:no Continuos space available\n");
			exit(0);
		}
		printf("Block Allocated\n");
		useddisk=useddisk+length;
		T = newnode();
		T->next = NULL;
		strcpy(T->fname,fn);
		T->start = blockno;
		T->length = length;
		
		printf("Before\n");
		if(F == NULL){
			F = L = T;
			printf("First block\n");
		}
		else {
			L->next = T;
			L = L->next;
			printf("remaining block\n");
		}

		for(int i = 0;i < length;i++)			//updating disk array 
			D[blockno++] = 0;
	}
	else{
		printf("No Disk Space Available\n");
		exit(0);
	}
}

int main(int argc, char const *argv[]){
	int c;

	printf("Enter the size of DiskSize\n");		
	scanf("%d",&disksize);

	if(disksize<1){
		printf("Invalid DiskSize\n");
		exit(0);
	}

	initDisk();					// inits the diskt to 1
	init();

	// start menu
	while(1){
		printf("\n__________________________________\n");
		printf("\n1:show bit Vector\n2:create file\n3:show directory\n4:delete file\nenter choice:\t");
		printf("\n__________________________________\n");
		scanf("%d",&c);
		switch(c){
			case 1 : displayBitVector();
					 break;
			case 2 : allocFile();
					 break;

			default :printf("Invalid Case Input \n"); 
		}

	}

 	return 0;
}