#include <stdio.h>

int main() {
    int ms, bs, nob, ef, n;
    int mp[50];   // process memory
    int tif = 0;  // total internal fragmentation
    int i, p = 0;

    // Input total memory
    printf("Enter the total memory available (in Bytes) -- ");
    scanf("%d", &ms);

    // Input block size
    printf("Enter the block size (in Bytes) -- ");
    scanf("%d", &bs);

    // Calculate number of blocks and external fragmentation
    nob = ms / bs;
    ef = ms - (nob * bs);

    // Input number of processes
    printf("Enter the number of processes -- ");
    scanf("%d", &n);

    // Input memory required for each process
    for (i = 0; i < n; i++) {
        printf("Enter memory required for process %d (in Bytes)-- ", i + 1);
        scanf("%d", &mp[i]);
    }

    printf("\nNo. of Blocks available in memory -- %d", nob);

    printf("\n\nPROCESS\tMEMORY REQUIRED\tALLOCATED\tINTERNAL FRAGMENTATION");

    // Allocation logic
    for (i = 0; i < n && p < nob; i++) {
        printf("\n%d\t\t%d", i + 1, mp[i]);

        if (mp[i] > bs) {
            printf("\t\tNO\t\t---");
        } else {
            printf("\t\tYES\t\t%d", bs - mp[i]);
            tif = tif + (bs - mp[i]);  // add internal fragmentation
            p++;  // block used
        }
    }

    // If memory full
    if (i < n) {
        printf("\nMemory is Full, Remaining Processes cannot be accommodated");
    }

    // Output fragmentation
    printf("\n\nTotal Internal Fragmentation is %d", tif);
    printf("\nTotal External Fragmentation is %d\n", ef);

    return 0;
}