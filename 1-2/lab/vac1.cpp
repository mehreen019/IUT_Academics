#include<bits/stdc++.h>
using namespace std;
int main(void){
    //long long n= 1000000000, n1=1000000000;
    //long long ans=(n*n1)%1000000000000000001;
    long long n,n1,m,ans=1;
    cin>>n;
    n1=n;
    long long ar[n];
    int i=0; bool l=0;
    while(n1--){
        cin>>m;
        ar[i]=m;
        i++;
        ans=(ans*m)%1000000000000000001;
    }
    for(int i=0;i<n;i++){
        //cout<<ar[i]<<" ";
        if(ans>=ar[i]){l=1; break;}
    }
    if(l)cout<<ans<<endl;
    else cout<<-1<<endl;
}
