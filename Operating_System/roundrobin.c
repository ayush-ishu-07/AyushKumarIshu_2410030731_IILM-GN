#include <stdio.h>

int main()
{
    int n, tq, time = 0, done = 0;
    int at[10], bt[10], rt[10], ct[10];
    int i, flag;

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("AT & BT of P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n");

    while(done < n)
    {
        flag = 0;
        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                flag = 1;
                printf("| P%d ", i + 1);

                if(rt[i] <= tq)
                {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    done++;
                }
                else
                {
                    rt[i] -= tq;
                    time += tq;
                }
            }
        }
        if(flag == 0)
            time++;
    }
    printf("|\n");

    printf("\nP  AT  BT  WT  TAT\n");
    for(i = 0; i < n; i++)
    {
        int tat = ct[i] - at[i];
        int wt  = tat - bt[i];

        avg_wt += wt;
        avg_tat += tat;

        printf("P%d  %d   %d   %d   %d\n",
               i + 1, at[i], bt[i], wt, tat);
    }

    printf("\nAvg WT = %.2f", avg_wt / n);
    printf("\nAvg TAT = %.2f\n", avg_tat / n);

    return 0;
}