// q sigma delta q0 f 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

struct DFA{
    int states;                     //COUNT
    int noofsymbol;                 //count
    int symbols[10];
    int delta[10][10];
    int nooffinal;
    int final[10];
};

struct DFA M;               //global machine

void accept(){
    int f;
    printf("Enter no of states::");
    scanf("%d",&M.states);
    printf("enter no of symbols::");
    scanf("%d",&M.noofsymbol);
    
    printf("Enter the input symbols\n");
    for (int i = 0; i < M.noofsymbol; i++){
        printf("Enter the s%d::",i+1);
        scanf(" %c",&M.symbols[i]);
    } 
    
    // for every input  symbol what transition is made 

    for (int i = 0; i < M.states; i++){
        for (int j = 0; j < M.noofsymbol; j++){
            printf("Enter the transition of Q%d over symbol %c::",i,M.symbols[j]);
            scanf(" %d",&M.delta[i][j]);
        }
    }
    
    printf("Enter no of Final states::");
    scanf("%d",&M.nooffinal);
    for (int i = 0; i < 10; i++)        // 10 size if funal
        M.final[i] = 0; 
    for (int i = 0; i < M.nooffinal; i++){
        printf("Enter Final%d::",i+1);
        scanf("%d",&f);
        M.final[f] = 1;
    }
 
}

void display(){
    printf("q1 is the initial state\n");
    printf("The set of States states(Q) :: { ");
    for (int i = 0; i < M.states; i++){               //size of final array
            printf("%d ,", i+1);
    }
    printf("\b};\n");
   
   printf("The set of Symbols (Sigma) :: { ");
    for (int i = 0; i < M.noofsymbol; i++){               //size of final array
            printf("%c ,", M.symbols[i]);
    }
    printf("\b};\n");
   
   
    printf("\n DELTA (d) \n\n");
    printf("  |");
    for (int j = 0; j < M.noofsymbol; j++)
        printf("%c ",M.symbols[j]);
    printf("|\n_____________\n");
    for (int i = 0; i < M.states; i++){
        printf("%d |",i+1);
        for (int j = 0; j < M.noofsymbol; j++){
            printf( "%d ",M.delta[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
       
    printf("The set of final states :: { ");
    for (int i = 0; i < 10; i++){               //size of final array
        if(M.final[i]==1)
            printf("%d ,", i);
    }
    printf("\b};\n");

}

int checkSymbol(char c){

    for (int i = 0; i < M.noofsymbol; i++){
        if(M.symbols[i]==c)
            return i;
    }
    return -1;
}


void execute(){
    char str[80];
    int i = 0;
    int currentstate = 0;

    printf("Enter the String to Check::");
    scanf(" %s",str);
    
    while(str[i]!='\0'){                   // -1 if symbol not found
        int symbolindex=checkSymbol(str[i]);
        if(symbolindex!=-1)
            currentstate = M.delta[currentstate][symbolindex];
        else{
            printf("Symbol not found in Sigma\n");
            break;
        }
        i++;
        printf("Executin----");
    }  
    if(M.final[currentstate]==1)
        printf("\n-------Valid String-------\n");
    else
        printf("\n-------Wrong String-------\n");

}

int main() {

    accept();
    display();
    execute();

    return 0;
}


/*

PS C:\Users\Admin\Desktop\TYEXAM\pexam\os> gcc dfa.c
PS C:\Users\Admin\Desktop\TYEXAM\pexam\os> .\a.exe
Enter no of states::3
enter no of symbols::2
Enter the input symbols
Enter the s1::0
Enter the s2::1
Enter the transition of Q0 over symbol 0::0
Enter the transition of Q0 over symbol 1::1
Enter the transition of Q1 over symbol 0::2
Enter the transition of Q1 over symbol 1::1
Enter the transition of Q2 over symbol 0::2
Enter the transition of Q2 over symbol 1::2
Enter no of Final states::1
Enter Final1::2
q1 is the initial state
The set of States states(Q) :: { 1 ,2 ,3 };
The set of Symbols (Sigma) :: { 0 ,1 };

 DELTA (d)

  |0 1 |
_____________
1 |0 1
2 |2 1
3 |2 2


The set of final states :: { 2 };
Enter the String to Check::011100
Executin----Executin----Executin----Executin----Executin----Executin----
-------Valid String-------
PS C:\Users\Admin\Desktop\TYEXAM\pexam\os> gcc dfa.c




*/

