#include <stdio.h>

#define MAX 25

int main() {
    int frag[MAX], b[MAX], f[MAX];
    int i, j, nb, nf, temp, lowest;
    int bf[MAX] = {0}, ff[MAX] = {0};

    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of the blocks:\n");
    for(i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    printf("\nEnter the size of the files:\n");
    for(i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
    }

    for(i = 0; i < nf; i++) {
        lowest = 10000;
        for(j = 0; j < nb; j++) {
            if(bf[j] == 0) {
                temp = b[j] - f[i];
                if(temp >= 0 && temp < lowest) {
                    ff[i] = j;
                    lowest = temp;
                }
            }
        }
        frag[i] = lowest;
        bf[ff[i]] = 1;
    }

    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");
    for(i = 0; i < nf; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1, f[i], ff[i] + 1, b[ff[i]], frag[i]);
    }

    return 0;
}
