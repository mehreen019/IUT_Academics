#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,k;
    cin>>n>>k;
    int r[n];
    for(int i=0;i<2*n;i++){
        cin>>r[i];
    }
    sort(r,r+(2*n));
    bool ans=1;
    //for(int i=0;i<2*n;i++) cout<<r[i]<<" ";
    //cout<<endl;
    for(int i=0;i<n;i++){
        //cout<<r[i+n]<<" "<<r[i]<<endl;
        if(r[i+n]-r[i]<k){ ans=0; break;}
    }
    if(ans){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
}
