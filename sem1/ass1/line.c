#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct  node
{
    char line[80];
    struct node *next;
}List;
    
/////////////////////////////////////////////////////////////

List *head=NULL;
List *last=NULL;    
char fname[10]="demo.txt";

void init()
{
    head=(List*)malloc(sizeof(List));
    head->next=NULL;
    last=head;
    printf("*********************************************************************\n");
    printf("\n\tKSR Line Editor v1.0 rDate 07/09/19\n");
    printf("\n*********************************************************************\n");
   
}

/////////////////////////////////////////////////////////////

int Lines()
{
    int i=0;
    List *temp=head;

    while(temp->next!=NULL)
    {
        //printf("Counting Line : %d \n",i);
        temp=temp->next;   
        i++;
    }
    return i;
}


/////////////////////////////////////////////////////////////

void read(char fname[10])
{ 
    FILE *fp=fopen(fname,"r+");
    char str[80];
  
    if(fp==NULL)
    {
        printf("File Could not be read!\n");
        exit(1);
    }
    int i=0;
    while(!feof(fp))
    {
        //printf("Reading Line: %d\t",i);
        if(!fgets(str,80,fp))
            break;
        List *temp=malloc(sizeof(List));
        temp->next=NULL;
        strcpy(temp->line,str);
        last->next=temp;
        last=temp;
        i++;
          //printf("Checking Next Line :\n");
    }

    printf("Reading Succefull!\n");
    fclose(fp);

}

/////////////////////////////////////////////////////////////////////////////////////////

void save(char fname[10])
{ 
    List *temp=head->next;

    FILE *fp=fopen(fname,"w");
    char str[80];
  
    if(fp==NULL)
    {
        printf("File Could not be saved!\n");
        exit(1);
    }
    int i=0;
    while(temp!=NULL)
    {
        //printf("Writing Line: %d\t",i);
        fputs(temp->line,fp);
        temp=temp->next;
    }

    printf("Writinging Successfull!\n");
    fclose(fp);

}


/////////////////////////////////////////////////////////////////////////////////////////

void DisplayMenu()
{
    printf("Please Select an Option\n");        
    printf("p : PRINT\ni : insert\na : append\nd : delete\nc : copy\nm : move\ns : save\nf : find\nh : help\n");
    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
}


/////////////////////////////////////////////////////////////////////////////////////////

void print(int n1,int n2)
{
    printf("PRINTING...\nlno\tline\n+++++++++++++++++++++++++\n");
    List *curr=head->next;
    int i=0;
    int l=Lines();

    if(n1<0 || n1>l || n2<0 || n2>l)
    {
        printf("Invalid input For Printing\n");
        exit(0);
    }

    else if(n1==0 && n2==0)
        printf("1\t%s\n",curr->line);

    else if(n2==0)
    {
        for(i=1;i<n1;i++)       // since current is already at first node i=1
            curr=curr->next;
        printf("%d\t%s\n",i,curr->line);
    }

    else
    {
        for(i=1;i<n1;i++)       
            curr=curr->next;
        for(i=n1;i<=n2;i++)
        {
            printf("%d\t%s\n",i,curr->line);
            curr=curr->next;
        }
    }

}

/////////////////////////////////////////////////////////////////////////////////////////

void insert(int n1)
{
    List *curr=head->next;
    List *prev=curr;
    int i=0;
    int l=Lines();
    char str[80];
    char ch;

    if(n1<0 || n1>l)
    {
        printf("Invalid Command for inserting\n");
        exit(0);
    }        
    for(i=0;i<n1;i++);
    {
        prev=curr;
        curr=curr->next;
    }

    printf("Enter the Line to Insert :");
    List *node=(List *)malloc(sizeof(List));
    i=0;
    while (i!=79)        // 80 char is the line limit
    {
        //printf("%d\t",i);
        scanf("%c",&ch);
        if(ch=='\n')
            break;
        else
            str[i++]=ch;
    }
    
    printf("Your Line :");
    puts(str);

    strcpy(node->line,str);
    prev->next=node;
    node->next=curr;
}

/////////////////////////////////////////////////////////////////////////////////////////

void append()
{
    int l=Lines();
    insert(l);
}

/////////////////////////////////////////////////////////////////////////////////////////

void delete(int n1,int n2)
{
    List *curr=head->next,*prev;
    List *curr2=head->next,*prev2;
    List *temp;

    int i=0;
    int l=Lines();

    if(n1<0 || n1>l || n2>l || n2<0)
    {
        printf("Invalid Command for Deleting\n");
        exit(0);
    }        
    for(i=0;i<n1;i++);
    {
        prev=curr;
        curr=curr->next;
    }

    for(i=0;i<n2;i++);
    {
        prev2=curr;
        curr2=curr2->next;
    }


    printf("Deleting the Lines :");
        prev->next=curr2;
    printf("Deleted the Lines :");      // if the last node is deleted last node reference becomes obsolete
    
    for(;curr!=curr2;curr=curr->next)
    {
        temp=curr;
        free(temp);
    }
    printf("Memory Freed :");
    
}


/////////////////////////////////////////////////////////////////////////////////////////

void move(int n1,int n2,int n3)
{
    List *curr=head->next,*prev;
    List *curr2=head->next,*prev2;
    List *curr3=head->next,*prev3;
    
    int i=0;
    int l=Lines();

    if(n1<0 || n1>l || n2>l || n2<0 || n3>l || n3<0 || n2<n1 || n1==0 || n2==0 || n3==0 || n1==n2 || n2==n3 || n1==n3)
    {
        printf("Invalid Command for Moving\n");
        exit(0);
    }        
    for(i=0;i<n1;i++);
    {
        prev=curr;
        curr=curr->next;
    }

    for(i=0;i<n2;i++);
    {
        prev2=curr;
        curr2=curr2->next;
    }

    for(i=0;i<n3;i++);
    {
        prev3=curr;
        curr3=curr3->next;
    }


    printf("Moving the Lines :");
        prev->next=curr3;
        curr3->next=curr;
        curr2->next=curr3->next;  
    printf("Moved the Lines :");     
    
    
}

/////////////////////////////////////////////////////////////////////////////////////////


void copy(int n1,int n2,int n3)
{
    List *curr=head->next,*prev;
    List *curr2=head->next,*prev2;

    int i=0;
    int l=Lines();

    if(n1<0 || n1>l || n2>l || n2<0 || n3>l || n3<0 || n2<n1 || n1==0 || n2==0 || n3==0 || n1==n2 || n2==n3 || n1==n3)
    {
        printf("Invalid Command for Copy\n");
        exit(0);
    }        
    for(i=0;i<n1;i++);
    {
        prev=curr;
        curr=curr->next;
    }

    for(i=0;i<=n3;i++);
    {
        prev2=curr;
        curr2=curr2->next;
    }
   
    printf("Moving the Lines :");
    for(curr;curr!=curr2;curr=curr->next)
    {
        List *temp =(List*)malloc(sizeof(List));
        strcpy(temp->line,curr->line);
        prev->next=temp;
        prev=curr; 
    }
    printf("Moved the Lines :");     
    
    
}

//////////////////////////////////////////////////////////////////////////



void main()
{
    int n,n1,n2,n3;
    n1=n2=n3=0;
    char c;
    char str[80];   
    init();    
    
    printf("File Initialised with demo File (demo.txt)\n");
    printf("*********************************************************************\n");

    read(fname);
    int l=Lines();
    printf("Lines are : %d\n",l);

    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\t\tInside Command Loop \n");
    printf("\ns++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    while(c!='q')
    {
        DisplayMenu();
        fgets(str,80,stdin);
        n=sscanf(str,"%c%d%d%d",&c,&n1,&n2,&n3);

        switch (c)
        {
        
        case  'p' :   print(n1,n2);
                      break;

        case  'i' :   insert(n1);
                      break;
        
        case  'a' :   append();
                      break;
        
        case  'd' :   delete(n1,n2);
                      break;

        case  'm' :   move(n1,n2,n3);
                      break;

        case  'c' :   //copy(n1,n2,n3);
                      break;

        case  's' :   save(fname); 
                      break;

        case  'q' :  printf("++++++++++Exiting+++++++++");
                     exit(0);

        default :
                    break;
        
        }


    }



}