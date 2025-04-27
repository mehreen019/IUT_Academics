#include<stdlib.h>
#include "task.h"
#include<stdio.h>
#include<string.h>
int main(void){
    SLL_Controller ctrl = SLL_NewController();
    int n,x; 
    char s[1000];
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf(" %s %d", s, &x);
        if(s[0]=='B'){ SLL_InsertBeg(&ctrl, x);}
        else if(s[0]=='E') SLL_InsertEnd(&ctrl,x);
    }
    SLL_Print(&ctrl);
    return 0;
}