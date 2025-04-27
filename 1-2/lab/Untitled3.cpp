#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,ans=0;
    cin>>n;
    int r[n];
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    for(int i=0;i<n-1; ){
        if(r[i+2]>max(r[i],r[i+1]) && i+2<n){ r[i+1]=0; i=i+2;}
        else if(r[i]>r[i+1] && i+1<n){ r[i+1]=0; i=i+2; }
        else{ r[i]=0; r[i+2]=0; i=i+3; }
    }
    for(int i=0;i<n;i++){
        ans+=r[i];
    }
    cout<<ans<<endl;
}
