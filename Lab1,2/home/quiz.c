#include<stdio.h>
#include"set.h"

int main(){
    char ans[10];
    for(int i=0;i<10;i++){
        printf("\nEnter %dth Answer A/B/C/D/N: ",i+1);
        scanf(" %c",&ans[i]);
    }
    int score = answer_checker(ans);
    printf("\n%d\n",score);
    return 0;
}