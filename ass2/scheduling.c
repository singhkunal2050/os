#include "scheduling.h"

int main() {
    system("clear");
    readProcess();
    displayProcess();

    int op = 0;
    do
    {
        printf("\nSelect an option:\n\t1]FCS\n\t2]SJF\n\t3]PSJF\n\t4]RR\n\t5]Priority\n::");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            sortFCFS();
            printGanttChart();
            display();

            break;
        
        case 2:
            sortSJF();
            //printGanttChart();
            display();
            break;

        case 3:
            break;
        
        case 4:
            break;

        case 5:
            break;

        case 6:
            printf("\n\tCiao !!!!\n\n");
            exit(0);

        default:
            printf("\nInvalid option selected!");
            break;
        }
    } while (op != 6);

    return 0;
}