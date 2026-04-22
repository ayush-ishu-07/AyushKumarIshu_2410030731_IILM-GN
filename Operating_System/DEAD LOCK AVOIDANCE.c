#include <stdio.h>

int main() {
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], work[10], total[10];
    int i, j, k, n, m;
    int finish[10] = {0}, count = 0;

    printf("Enter the no. of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter the claim (Max) matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the total resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &total[i]);
    }

    // Calculate available = total - allocated
    for(i = 0; i < m; i++) {
        avail[i] = 0;
        for(j = 0; j < n; j++) {
            avail[i] += alloc[j][i];
        }
        avail[i] = total[i] - avail[i];
        work[i] = avail[i];
    }

    // Calculate need matrix
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\n");

    // Safety Algorithm
    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int possible = 1;

                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {
                    printf("All the resources can be allocated to Process %d\n", i + 1);

                    printf("Available resources are: ");
                    for(k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                        printf("%d ", work[k]);
                    }

                    printf("\nProcess %d executed?: y\n\n", i + 1);

                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if(!found) {
            printf("System is NOT in safe state\n");
            return 0;
        }
    }

    printf("System is in safe mode\n");
    printf("The given state is safe state\n");

    return 0;
}
