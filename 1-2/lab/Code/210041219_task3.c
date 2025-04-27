#include<stdlib.h>
#include "task.h"
#include<stdio.h>
#include<string.h>
int main(void){
    SLL_Controller ctrl = SLL_NewController();
    int n,m,x; 
    scanf("%d %d", &n, &m);
    int arr1[n], arr2[m];
    //SLL_Print(&ctrl);
    for(int i=1;i<=n;i++){
        scanf("%d", &arr1[i]);
    }
    for(int i=1;i<=n;i++){
        SLL_Insert(&ctrl, arr1[i]);
    }
    for(int i=0;i<m;i++){
        scanf("%d", &arr2[i]);
    }
    for(int i=0;i<m;i++){
        SLL_Insert(&ctrl, arr2[i]);
    }
    SLL_Print(&ctrl);
}