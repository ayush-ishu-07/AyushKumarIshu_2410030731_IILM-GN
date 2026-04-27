#include<stdio.h>

#define MAX 25

int main() {
    int b[MAX], f[MAX], frag[MAX];
    int bf[MAX]={0}, ff[MAX]={0};
    int nb, nf, i, j, temp, max;

    printf("\nMemory Management Scheme - Worst Fit\n");

    printf("Enter number of blocks: ");
    scanf("%d", &nb);

    printf("Enter number of files: ");
    scanf("%d", &nf);

    printf("\nEnter block sizes:\n");
    for(i=1;i<=nb;i++){
        printf("Block %d: ",i);
        scanf("%d",&b[i]);
    }

    printf("\nEnter file sizes:\n");
    for(i=1;i<=nf;i++){
        printf("File %d: ",i);
        scanf("%d",&f[i]);
    }

    for(i=1;i<=nf;i++){
        max = -1;

        for(j=1;j<=nb;j++){
            if(bf[j]==0){
                temp = b[j] - f[i];

                if(temp >= 0 && temp > max){
                    ff[i] = j;
                    max = temp;
                }
            }
        }

        frag[i] = max;
        bf[ff[i]] = 1;
    }

    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment\n");

    for(i=1;i<=nf;i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
        i, f[i], ff[i], b[ff[i]], frag[i]);
    }

    return 0;
}