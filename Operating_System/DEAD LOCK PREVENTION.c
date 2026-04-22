#include <stdio.h>

int main() {
    char job[10][10];
    int time[10], avail;
    int temp[10], tem[10];
    int safe[10];
    int ind = 0, i, j, q, n, t;

    printf("Enter no of jobs:");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter name and time:");
        scanf("%s %d", job[i], &time[i]);
    }

    printf("Enter the available resources:");
    scanf("%d", &avail);

    // Copy arrays
    for(i = 0; i < n; i++) {
        temp[i] = time[i];
        tem[i] = i;
    }

    // Sorting
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(temp[i] > temp[j]) {
                t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;

                t = tem[i];
                tem[i] = tem[j];
                tem[j] = t;
            }
        }
    }

    // Safe sequence check
    for(i = 0; i < n; i++) {
        q = tem[i];
        if(time[q] <= avail) {
            safe[ind++] = q;
            avail -= time[q];
        } else {
            printf("No safe sequence\n");
            return 0;
        }
    }

    // Exact output format
    printf("Safe sequence is: ");
    for(i = 0; i < ind; i++) {
        printf("%s %d", job[safe[i]], time[safe[i]]);
        if(i != ind - 1) printf(", ");
    }
    printf(".\n");

    return 0;
}
