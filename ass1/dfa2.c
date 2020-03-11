#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>

void count(char option, char *fname) {
    printf("inside count");
    int handle, ccnt = 0, wcnt = 0, lcnt = 0;
    char ch;

    // hhandle is a pointer  to a file
    handle = open(fname, O_RDONLY);

    if(handle == -1) {
        printf("\nUnable to open the file!");
        return;
    }

    // read each line character by character
    while (read(handle, &ch, 1)) {
        ccnt++;
        if (ch == ' ' || ch == '\t')
            wcnt++;
        else if (ch == '\n') {
            lcnt++;
            wcnt++;
        }
    }

    close(handle);
    
    switch (option)
    {
    case 'c':
        printf("\nTotal no of characters in file = %d\n", ccnt);
        break;
    
    case 'w':
        printf("\nTotal no of words in file = %d\n", wcnt);
        break;

    case 'l':
        printf("\nTotal no of lines in file = %d", lcnt);
        break;

    default:
        printf("\n\tInvalid OPtionn\n");
        break;
    }
}

void search(char op, char *fname, char *key) {
    printf("\nSearching........");
    FILE *fp = fopen(fname, "r");
    char str[80];
    char *temp;
    int i = 0, cnt = 0, flag = 1;

    while (fgets(str, 80, fp) != NULL) {
        printf("first while");
        flag = 1;
        while(flag) {
            //printf("second while");
            i++;
            temp = strtok(str, " ");
            if(temp == NULL)
                flag = 0;
            else{
                switch (op)
                {
                case 'f':
                    if(strcmp(key, temp) == 0) {
                        printf("\nFirst occurence of the key found at line %d\n", i);
                        fclose(fp);
                        return;
                    }
                    break;
                case 'a':
                    if(strcmp(key, temp) == 0) {
                        printf("\nkey found at line %d", i);    
                    }
                    break;
                case 'c':
                    if(strcmp(key, temp) == 0) {
                        //printf("key found at line %d", i);
                        cnt++;
                    }
                default:
                    break;
                }
            }
        }
    }
    if (op == 'c') {
        printf("\nKey occured total %d times.", cnt);
    }
    fclose(fp);
}

void typeline(char op, char *fname) {
    printf("inside typeline");
}

int main() {
    int n;
    char t1[10], t2[10], t3[10], t4[10];
    char str[80];

    while(1) {
        printf("\nshady_shell $]");
        fgets(str, 80, stdin);
        //scanf("%[^\n]s", str);
        // tokenize the string
        n = sscanf(str, "%s %s %s %s", t1, t2, t3, t4);
        switch (n) {
        case 1:
            if (fork()==0) // create a child process
            {
                execlp(t1, t1, NULL);
                wait(0); // wait until  the process is done executing
            }
            
            break;
        case 2:
            if(fork()==0) {
                execlp(t1, t1, t2, NULL);
                wait(0);
            }
            break;

        case 3: // 3 word command: count c test.txt
            if(strcmp(t1, "count") == 0) {
                count(t2[0],t3);
            } else if(strcmp(t1, "typeline") == 0){
                typeline(t2[0], t3);
            } else if(fork()==0) {
                execlp(t1, t1, t2, t3, NULL);
                wait(0);
            }
            break;

        case 4:
            if(strcmp(t1, "search") == 0) {
                search(t2[0], t3, t4);
            } else if(fork()==0) {
                execlp(t1, t1, t2, t3, t4, NULL);
                wait(0);
            }
            break;

        default:
            printf("invalid no of arguments!");
        }
    }

    return 0;
}