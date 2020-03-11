#include<stdio.h>
#include <stdlib.h>
#define MXSZ 10


int framesize;
int ptable[MXSZ];
int len;
int refString[MXSZ];

typedef struct Stack{
    int top;
    int arr[MXSZ];
}Stack;

Stack S; 

void initStack(){
    S.top=-1;
    for (int i = 0; i < MXSZ; ++i){
        S.arr[i]=-1;
    }
}

void push(int number){
    S.arr[++S.top]=number;
}

void updateStack(){          //deletes the one at 0 index and shifts upper stack below
    for (int i = S.top; i >0; --i)
        S.arr[i-1]=S.arr[i];
    S.top--;
}


void accept(){
    printf("Enter the frame size::");
    scanf("%d",&framesize);

    printf("Enter the length of String::");
    scanf("%d",&len);
    
    printf("Enter the String\n");
    for (int i = 0; i < len; i++){
        printf("Enter %i::",i+1);
        scanf("%d",&refString[i]);
    }
        
}

void display(){
    printf("Reference   String ::\n");
    for (int i = 0; i < len; i++){
        printf("%d\t",refString[i]);
    }
    printf("\n");
}

int checkFault(int current){
    for (int j = 0; j < framesize;j++){
        if(ptable[j]==current)
            return j;                       // no pf
    }
    return -1;                              //pf
}



void fifo(){
    int index = 0;          // for tracking the index to insert according to fifo
    int fault = 0;

    for (int i = 0; i < len; i++){
        int current = refString[i];
            if(checkFault(current) == -1){            //pagefault
                ptable[index] = current;
                fault++;
                index = (index + 1) % framesize;
            }
            else{                                   // no pf
                printf("no page fault for %d \n",current);
            }    
    }

    printf("Total Page fault :: %d\n",fault);
}

int getLruIndex(){
    for (int i = 0; i < framesize; ++i){
        if(ptable[i]==S.arr[0])  
            return i;
        else
            printf("not getting lru index for %d\n",S.arr[0]);
    }
}

void lru(){
    int index = 0;          // for tracking the index to insert according to fifo
    int fault = 0;
    initStack();


    for (int i = 0; i < framesize; ++i){
        int current = refString[i];
        if(checkFault(current) == -1){            //pagefault
            ptable[i] = current;
            fault++;
            push(current);
            updateStack();
        } 
    }


    for (int i = framesize; i < len; i++){
        int current = refString[i];
            if(checkFault(current) == -1){            //pagefault
                index=getLruIndex();
                ptable[index] = current;
                fault++;
                push(current);
                updateStack();
                // index = (index + 1) % framesize;
            }
            else{                                   // no pf
                printf("no page fault for S%d::%d \n",i,current);
            }    
    }

    printf("Total Page fault :: %d\n",fault);
}

int main(int argc, char const *argv[])
{
    int op;
    do{
        printf("______________________________________________________________\n");
        printf("Select 1 for accept\n2 for display\n3 for checking pagefault(fifo)\n4 for checking pagefault(lru)\n");
        printf("______________________________________________________________\n");
        
        scanf("%d",&op);
        
        switch(op){
            case 1:   accept();
                      break;
            case 2:   display();
                break;
            case 3:   fifo();
                break;   
            case 4:   lru();
                break;   
        }

    } while (op != 0);
    return 0;
}
