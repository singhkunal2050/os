#include <stdio.h>
#include <stdlib.h>

 int mem[1000],reg[4];
int lc;
int pc;

int load(){
	char fname[10];
	FILE *fp;
	int address,content;

	printf("Choose a file\n");
	scanf("%s",fname);

	fp=fopen(fname,"r");
	if(fp==NULL){
		printf("File not found\n");
		return 0;
	}
	else{
		while(!feof(fp)){
			fscanf(fp,"%d %d",&address,&content);
			if(address==-1)
				pc=content;
			else{
				lc=address;
				mem[address]=content;
			}		
		}
		fclose(fp);
		return 1;
	}
}


void execute(){
	int opcode,r,addr;		// part of instruction
	int ins;				// program counter
	int cc[6]={0};			// concditoinal code

	while(1){
		ins=mem[pc];
		addr=ins%1000; 
		ins=ins/1000;
		r=ins%10;
		opcode=ins/10;

		switch(opcode){
			case 0:printf("BYE\n");
					exit(0);
					break;

			case 1 : reg[r] =reg[r]+mem[addr];
					 pc++;
					break;

			case 2 : reg[r] =reg[r]-mem[addr];
					 pc++;
					break;

			case 3 : reg[r] =reg[r]*mem[addr];
					 pc++;
					break;

			case 8 : reg[r] =reg[r]/mem[addr];
					 pc++;
					break;

			case 4: reg[r]=mem[addr];
					 pc++;
					break;

			case 5: mem[addr]=reg[r];
					 pc++;
					break;

			case 6:  if(reg[r]<mem[addr])
							cc[0]=1;
					 else if(reg[r]<=mem[addr])
							cc[1]=1;
					 else if(reg[r]==mem[addr])
							cc[2]=1;
					 else if(reg[r]>mem[addr])
							cc[3]=1;
					 else if(reg[r]>=mem[addr])
							cc[4]=1;
					 else 
					 		cc[5]=1;
					 pc++;
					 break;
				 
			case 7: if(cc[r]==1 || r==5)	// comarison successful or any jump
						pc=addr;
					else
						pc++;
					break;

			case 9:	printf("Enter::\n");
					scanf("%d",&mem[addr]);
					pc++;
					break;

			case 10:printf("%d\n",mem[addr]);
					pc++;
					break;
		}	
	}
}


int main(int argc, char const *argv[])
{
	load();
	execute();
	return 0;
}