#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAXSZ 10

typedef struct PROCESS
{   
    char name[20];
    int at, bt, tat, wt, ct, st, ft;
    int finish_flag;
}PROCESS;

// Global variables
PROCESS p[MAXSZ];
PROCESS buff[MAXSZ];
int processCount, i, j, k;
float totalTAT, totalWT, avgTAT, avgWT;
int sysClock;

// Function to accept all the processes
void readProcess() {
    printf("\nEnter how many processes: ");
    scanf("%d", &processCount);
    srand(time(0));
    for (i = 0; i < processCount; i++) {
        printf("\nEnter process name: ");
        scanf("%s", p[i].name);
        //srand(time(0));
        p[i].at = rand() % 5;
        int t = rand() % 10;
        if(t != 0) {
            p[i].bt = t;
        } else {
            p[i].bt = 3;
        }
        p[i].finish_flag = 0;
    }
}

// function to display stored process
// for debug purposes'
void displayProcess() {
    for (i = 0; i < processCount; i++)
    {
        printf("\n\npname = %s\narrival time = %d\nburst time = %d", p[i].name, p[i].at, p[i].bt);
    }
    printf("\n--------------------------------------------------------------------------------\n");
}

void displayProcessBuff() {
    for (i = 0; i < processCount; i++)
    {
        printf("\n\npname = %s\narrival time = %d\nburst time = %d", buff[i].name, buff[i].at, buff[i].bt);
    }
    printf("\n--------------------------------------------------------------------------------\n");
}

// function which loads the processes into a buffer arr
void loadBuff() {
    for (i = 0; i < processCount; i++)
    {
        buff[i] = p[i];
    }
    
}

void arrSort() {
    PROCESS temp;

    for (i = 0; i < processCount; i++) {
        for (j = 0; j < processCount - i - 1; j++) {
            if(buff[j].at > buff[j + 1].at) {
                temp=buff[j + 1];
			    buff[j + 1]=buff[j];
			    buff[j]=temp;
            }
        }
    }
}

// FCFS sort function
void sortFCFS() {
    loadBuff();
    int clock = 0;
    arrSort();
    displayProcessBuff();

    // calculate wt, tat & rest
    //printf("\n\n  GanttChart:\n") ;
    //printf("__________________________________________________\n");
    for (i = 0; i < processCount; i++) {
        if(buff[i].at > clock) {
            while (buff[i].at > clock) {
                clock++;
                printf(" idle ");
            }   
        }
        buff[i].st = clock;
        clock += buff[i].bt;
        buff[i].ft = clock;
        buff[i].wt = buff[i].st - buff[i].at;
        buff[i].tat = buff[i].ft - buff[i].at;
        totalTAT += buff[i].tat;
        totalWT += buff[i].wt;

        //printf("|%d  ", buff[i].st);
        //printf("%s  ", buff[i].name);
    }
    //printf("|%d  ", buff[processCount-1].ft);
    //printf("\n__________________________________________________\n\n");
    avgTAT = totalTAT / processCount;
    avgWT = totalWT / processCount;
}
// tat = finish - arrival
// wt = start - arrival

// returns the  process no which has the shortest burst time
int getProcess() {
    int min = 999, no = -1;
    //printf("\ninside get process sysClock = %d", sysClock);
    int l;

    for (l = 0; l < processCount; l++) {
        if (buff[l].at <= sysClock) {
            // storing the min bt and index
            if(!buff[l].finish_flag && buff[l].bt < min) {
                min = buff[l].bt;
                no = l;
            }
        }
    }
    //printf("\n\treturning %d", no);
    return no;
}

// SJF function
void sortSJF() {
    loadBuff();
    sysClock = 0;
    arrSort();
    displayProcessBuff();
    int count = 0;
    
    if(buff[0].at > sysClock) {
        while (buff[0].at > sysClock) {
            sysClock++;
            printf(" idle ");
        }   
    }
    printf("\n\n  GanttChart:\n") ;
    printf("__________________________________________________________________________________\n");
    for (j = 0; j < processCount; j++) {
        i = getProcess();
        if(i == -1) {
            printf(" idle ");
            while (getProcess() == -1) {
                sysClock++;
            }
        } else {
            buff[i].st = sysClock;
            sysClock += buff[i].bt;
            buff[i].ft = sysClock;
            buff[i].wt = buff[i].st - buff[i].at;
            buff[i].tat = buff[i].ft - buff[i].at;
            buff[i].finish_flag = 1;
            totalTAT += buff[i].tat;
            totalWT += buff[i].wt;

            printf("|%d  ", buff[i].st);
            printf("%s  ", buff[i].name);
        }
    }
    printf("|%d  ", buff[i-1].ft);
    printf("\n________________________________________________________________________________\n\n");
}

void printGanttChart() {
    k = 0 ;
    int clock = 0;

    printf("\n\n  GanttChart:\n") ;
    printf("__________________________________________________________________________________\n");
    while (k < processCount) {
        if(buff[k].at > clock) {
            while (buff[k].at > clock) {
                clock++;
                printf("|%d idle ", clock-1);
            }   
        }
        clock += buff[k].bt;

        printf("|%d  ", buff[k].st);
        printf("%s  ", buff[k].name);

        k++;
    }
    printf("|%d  ", buff[k-1].ft);
    printf("\n________________________________________________________________________________\n\n");

}

void display()
{
    printf("\n--------------------------------------------------------------------------------\n") ;
    printf("Process  ArrivalTime  BurstTime  CPUTime  TurnAroundtime  WaitTime\n");
    printf("--------------------------------------------------------------------------------\n");
    for(i=0 ; i<processCount ; i++)
       printf("%s\t  %d\t\t%d\t  %d\t   %d\t\t   %d\n",buff[i].name,buff[i].at,buff[i].bt,buff[i].ct,buff[i].tat,buff[i].wt) ;
    printf("--------------------------------------------------------------------------------") ;
    printf("\n\nTotal Turn Around Time: %f",totalTAT) ;
    printf("\nTotal Wait Time: %f",totalWT) ;
    printf("\n\nAverage Turn Around Time: %f",avgTAT) ;
    printf("\nAverage Wait Time: %f\n",avgWT) ;
}