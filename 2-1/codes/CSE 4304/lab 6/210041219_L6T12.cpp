#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
int main(void){
    while(1){
    int n;
    cin>>n;
    if(n==0) break;
    int r[n];
    for(int i=0;i<n;i++) cin>>r[i];
    sort(r,r+n);
    int ans=r[0],res=0;
    for(int i=1;i<n;i++){
        ans=ans+r[i];
        //if(i==1) res=0;
        res+=ans;
    }
    cout<<res<<endl;
    }
}
