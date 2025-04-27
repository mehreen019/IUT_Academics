#include "task1.h"
#include<bits/stdc++.h>
using namespace std;
int main(void){
    SLL_Controller ctrl = SLL_NewController();
    int n,x;
    string s;
    scanf("%d", &n);
    SLL_Print(&ctrl);
    for(int i=1;i<=n;i++){
        cin>>s>>x;
        if(s=="BEGINNING"){ SLL_InsertBeg(&ctrl, x); SLL_Print(&ctrl);}
        else if(s=="END") SLL_InsertEnd(&ctrl,x);
    }
    SLL_Print(&ctrl);
}