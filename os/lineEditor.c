// SLIM SHADY //
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct NODE
{
    char line[100];
    struct NODE *next;
}NODE;
NODE *head, *last;

void init() {
    head = (NODE *)malloc(sizeof(NODE));
    head->next = NULL;
    last = head;
}

NODE *getnode(NODE *head, char *data) {
    NODE *temp = (NODE *)malloc(sizeof(NODE));
    temp->next = NULL;
    strcpy(temp->line, data);
    return temp;
}

int countLine(NODE *head) {
    NODE *temp = head->next;
    int i = 1;

    while(temp != NULL) {
        //printf("\n%d: %s", i, temp->line);
        i++;
        temp = temp->next;
    }

    return i;
}

// this function will load the file
void load(char *fname) {
    char msg[100];
    FILE *fp = fopen(fname, "r+");

    if(fp != NULL) {
        last = head;
        while(!feof(fp)) {
            if(!fgets(msg, 100, fp))
                break;
            last->next = getnode(head, msg);
            last = last->next;
        }
        fclose(fp);
    } else {
        printf("\nFile canot be opened!");
        exit(0);
    }
}

// insert a new line in the given position
void insert(NODE *head, int n1) {
    NODE *back = head, *curr = back->next, *temp = NULL;
    char str[100];

    if(n1 <= 0 && n1 > countLine(head)) {
        printf("\nInvalid position to insert a line!\n");
        return;
    }

    // skipping n1 - 1 lines
    for(int i = 1; i < n1; i++) {
        back = curr;
        curr = curr->next;
    }
    printf("\nEnter the line: ");
    //fgets(str, 100, stdin);
    scanf(" %[^\n]s", str);
    strcat(str, "\n");

    // now store the new line in a node
    temp = getnode(head, str);
    temp->next = curr;
    back->next = temp;
}

//this function will add a line to the last
void append(NODE *head) {
    insert(head, countLine(head) + 1);
}

/// this function will  save the LL contents into the file
void save(NODE *head) {
    char name[10];
    printf("\nEnter the filename to save: ");
    scanf("%s", name);
    FILE *fp = fopen(name, "w");
    NODE *temp = head->next;

    if(fp != NULL) {
        while (temp != NULL) {
            fputs(temp->line, fp);
            temp = temp->next;
        }
        fclose(fp);
        printf("\n\tFile saved !!\n");
    } else {
        printf("\nCannot open file!");
        return;
    }
}

// this function will delete lnes between n1 and n2
void delete(NODE *head, int n1, int n2) {
    if(n1 <= 0 && n1 > countLine(head) && n2 <= 0 && n2 > countLine(head)) {
        printf("\nInvalid positions entered!");
        return;
    }

    NODE *back = head, *curr = head;
    ;

    // skipping n1 -1 lines
    for(int i = 0; i < n1; i++) {
        back = back->next;
    }
    
    // skipping n2 - 1 lines
        for(int j = 0; j < n2; j++) {
        curr = curr->next;
    }

    // now attach back to curr1
    back->next = curr;
}

// // this function will copy n2 lines from n1 and paste it after n3
// void copy(NODE *head, int n1, int n2, int n3) {
//     int len = countLine(head);

//     if(n1 <= 0 && n1 > len && n2 <= 0 && n2 > len) {
//         printf("\nInvalid positions entered!");
//         return;
//     }

//     NODE *back = head, *curr = head->next;
//     NODE *back1 = head, *curr1 = head->next;
//     NODE *back2 = head, *curr2 = head->next; 
//     NODE *temp = NULL;

//     // skipping n1 - 1 lines
//     for(int i = 0; i < len; i++) {
//         back = curr;
//         curr = curr->next;
//     }
//     // skipping n2 - 1 lines
// //    for(int i = 0; i < len; i++) {
// //        back1 = curr1;
// //        curr1 = curr1->next;
// //    }
//     // skipping n3 - 1 lines
//     for(int i =0; i < len; i++) {
//         back2 = curr2;
//         curr2 = curr2->next;
//     }

//     char msg[100];

//     // now copy each node from n1 to n2 and attach it after n3
//     while(n1 < n2) {
//         strcpy(msg, back->next->line); // storing the line into msg
//         temp = getnode(head, msg);
//         temp->next = back2->next; // attahced it after n3
//         back2 = temp; // incremented the back2 pointer
//         curr2 = curr2->next; // incremented the curr2 pointer

//         // now increment the pointers of n1 to copy next node
//         back = curr;
//         curr = curr->next;
//     }

//     printf("\nDONE copying!\n");
// }

void display() {
    NODE *temp = head->next;
    int i = 1;

    while(temp->next != NULL) {
        printf("\n%d: %s", i, temp->line);
        temp = temp->next;
        i++;
    }
    printf("\nTOTAL LINES: %d", countLine(head) - 1);
}

void copy(NODE *head,int n1 , int n2 , int d ){
    NODE *temp = head->next;
    NODE *newlines = (NODE *)malloc(sizeof(NODE));
    newlines->next = NULL;
    NODE *newlinesref = newlines;

    for (int i = 0; i < n1;i++){
        temp = temp->next;
        printf("travesring\n");
    }
    
    for (int i = 0; i < n2;i++){
        newlines->next = getnode(head,temp->line);
        temp = temp->next;
        newlines = newlines->next;
        printf("COPYING Line\n");
    }

    NODE *curr = head->next;
    NODE *prev =curr;
    
    for (int i = 0; i < d; i++){
        prev = curr;
        curr = curr->next;
        printf("Traversing again");
    }

    prev->next = newlinesref;
    while (newlinesref->next!=NULL)
        newlinesref = newlinesref->next;
    newlinesref->next = curr;

}

int main(int argc, char* argv[]) {
    int op, n, n1, n2, n3;
    char fname[10];

    init();
    // system("clear");

    do {
        printf("\n_____________________________________________________________________________\n");
        printf("Enter a choice: \n");
        printf("_____________________________________________________________________________\n");
		printf("\n1.Load\n2.Insert\n3.Save\n4.Delete\n5.Copy\n6.Exit\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("\nChoice :: ");
		scanf("%d",&op);
        printf("-----------------------------------------------------------------------------\n");


		switch(op)
		{
			case 1:
                if(argc > 1) {
                    load(argv[1]);
                } else {
                    printf("\nFilename: ");
                    scanf("%s", fname);
                    load(fname);
                }
                display();
				break;

			case 2:
                printf("\nAt which position would you like to insert: ");
                scanf("%d", &n1);
                insert(head, n1);
                display();
				break;

			case 3:
                save(head);
				break;

            case 4:
                printf("\nEnter the lines you wanna delete(n1, n2): ");
                scanf(" %d%d", &n1, &n2);
                delete(head, n1, n2);
                display();
                break;

            case 5:
                printf("Enter n1 n2 n3\n");
                scanf("%d%d%d",&n1,&n2,&n3);
                copy(head, n1, n2, n3);
                break;
                
            case 6:
                printf("\nLater Homie\n");
                exit(0);

            default:
                printf("\nInvalid option selected!\n");
		}
    } while(op != 6);

    return 0;
}