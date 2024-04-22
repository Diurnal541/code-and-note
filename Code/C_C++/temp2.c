#include <stdio.h>
int main(){
    printf("\ti\ti*i\ti*i*i\n");
    printf("---------------------------\n");
    for (int i = 1; i <= 4;i++){
        printf("\t%d\t%d\t%d\n", i, i * i, i * i * i);
    }
    return 0;
}
