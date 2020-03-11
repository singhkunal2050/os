#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char line[80];
	struct node *next;
}List;

List *head=NULL;
List *last=NULL;
char fname[10]="demo.txt";

void init(){
	head=(List*)malloc(sizeof(List));
	head->next=NULL;
	last=head;
}

int lines(){
	int i=0;
	List *temp=head->next;
	while(temp!=NULL){
		i++;
		temp=temp->next;
	}
	return i;
}

void read(){
	FILE *fp=fopen(fname,"r+");
	char buff[80];
	int i=0;

	if(fp==NULL){
		printf("Cannot read file\n");
		exit(0);
	}
	else{
		while(!feof(fp)){
			if(!fgets(buff,80,fp))
				break;
			List *temp=(List*)malloc(sizeof(List));
			strcpy(temp->line,buff);
			last->next=temp;
			last=temp;
			printf("reading %d\t%s\n",i++,temp->line );
		}
	}
	fclose(fp);
}


void insert(int n){
	if(n>lines() || n<0){
		printf("Invlaid posn for insert\n");
		exit(0);
	}
	else{
		char buff[80];
		printf("Enter the line to insert\n");
		// scanf(" %[^\n]s",buff);
		fflush(stdin);
		gets(buff);

		List *curr=head->next;
		List *prev=curr;

		int i=0;
		while(i++<n){
			prev=curr;
			curr=curr->next;
			printf("while %d\t",i);
		}

		List *temp=(List*)malloc(sizeof(List));
		strcpy(temp->line,buff);
		prev->next=temp;
		temp->next=curr;
	}
}

void print(){
	int i=0;
	List *temp=head;
	while(temp->next!=NULL){
		printf("line %d::\t%s\n",i++,temp->line );
		temp=temp->next;
	}
}

void save(){
	FILE *fp=fopen(fname,"w+");
	if(fp==NULL){
		printf("File not written\n");
	}
	else{
		List *temp=head->next;
		while(temp->next!=NULL){
			fputs(temp->line,fp);
			temp=temp->next;
		}
	}
}

void delete(){}

void copy(){}

void append(){}

void main()
{
    int n;
    int op;
 
 	init();   
    do{
		printf("+++++++++++++++++KSR LL 1.2++++++++++++++++\n");
   		printf("0::Exit\n1::READ\n2::Insert\n3::Delete\n4::Append\n5::Copy\n6::save\n7::print\n");
   		printf("+++++++++++++++++++++++++++++++++++++++++++\n");
   		scanf("%d",&op);
   		switch(op){
   			case 0:exit(0);
   			case 1:read();
   					break;
   			case 2:	printf("Enter the line number to insert\n"); 
					scanf("%d",&n);
   					insert(n);
   					break;
   			case 3:delete();
   					break;
   			case 4:append();
   					break;
   			case 5:copy();
   					break;
   			case 6:save();
   					break;
   			case 7:print();
   					break;
   			default :printf("Enter correct ip\n");
		}
    }while(op!=0);

}