#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sch.h"

int main(int argc, char const *argv[])
{
	int op=-1;

	readProcess();
	display();

	do{
		printf("Choose the algorith\n0::EXIT\n1::FCFS\n2::SJF\n3::RR\n4::Priority\n");
		scanf("%d",&op);
		switch(op){
			case 0: exit(0);
					break;
			case 1 : executeFCFS();
					 display();
					 // printChart();
					break;	

			case 2 : executeSJF();
					 display();
					 // printChart();
					break;	

			default : printf("Enter correct ip\n");
					break;
		}
	}while(op!=0);

	return 0;
}



