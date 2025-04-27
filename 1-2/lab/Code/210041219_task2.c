#include<stdlib.h>
#include "task.h"
#include<stdio.h>
#include<string.h>
int main(void){
    SLL_Controller ctrl = SLL_NewController();
    int n,x; 
    scanf("%d", &n);
    int arr[n];
    SLL_Print(&ctrl);
    for(int i=1;i<=n;i++){
        scanf("%d", &arr[i]);
    }
    for(int i=1;i<=n;i++){
        SLL_Element* foundElement = SLL_Find(&ctrl, arr[i]);
        if(!foundElement) SLL_Insert(&ctrl, arr[i]);
    }
    SLL_ReversePrint(&ctrl);
}