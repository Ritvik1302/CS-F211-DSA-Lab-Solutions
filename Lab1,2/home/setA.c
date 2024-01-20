#include <stdio.h>
#include "set.h"
char key[10]={'A','A','A','A','A','A','A','A','A','A'};
int answer_checker(char * ans){
    int score=0;
    for(int i=0;i<10;i++){
        if(ans[i]=='N')continue;
        else if (ans[i]==key[i])score+=4;
        else score-=1;
    }
    return score;
}