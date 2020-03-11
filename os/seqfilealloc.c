#include<stdio.h>
#include <stdlib.h>
#define MXSZ 10

long long int bitvector;				// stores the bit sequence of blocks 1|0 for free|taken

typedef struct filent{
	char name[MXSZ];
	int startblockno;
	int lengthofblock;	
	struct filent *next;
}fileRecord;



void accept(){
	printf("Enter the number of blocks\n");
	scanf("%d",&blocks);

}



int main(int argc, char const *argv[]){

	accept();	



	return 0;
}