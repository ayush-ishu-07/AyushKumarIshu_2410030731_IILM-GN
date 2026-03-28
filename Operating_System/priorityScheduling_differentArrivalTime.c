#include <stdio.h>

struct process {
    int pid, at, bt, priority;
    int ct, wt, tat, completed;
};

int main() {
    int n, i, time = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);
        printf("PID: "); scanf("%d", &p[i].pid);
        printf("Arrival Time: "); scanf("%d", &p[i].at);
        printf("Burst Time: "); scanf("%d", &p[i].bt);
        printf("Priority: "); scanf("%d", &p[i].priority);
        p[i].completed = 0;
    }

    int gantt_pid[100], gantt_time[100], k = 0;

    while(completed < n) {
        int idx = -1;
        int highest_priority = 999;

        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].completed == 0) {
                if(p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            
            gantt_pid[k] = p[idx].pid;
            gantt_time[k] = time;
            k++;

            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = 1;
            completed++;
        } else {
            time++; 
        }
    }

    gantt_time[k] = time;

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].priority,
            p[i].ct, p[i].tat, p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nGantt Chart:\n ");

    for(i = 0; i < k; i++) {
        printf("--------");
    }
    printf("\n|");

    for(i = 0; i < k; i++) {
        printf("  P%d  |", gantt_pid[i]);
    }

    printf("\n ");
    for(i = 0; i < k; i++) {
        printf("--------");
    }

    printf("\n%d", gantt_time[0]);
    for(i = 1; i <= k; i++) {
        printf("      %d", gantt_time[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
