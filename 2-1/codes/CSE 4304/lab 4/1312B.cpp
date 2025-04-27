#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,tst;
    cin>>tst;
    while(tst--){
        cin>>n;
        int r[n];
        for(int i=0;i<n;i++) cin>>r[i];
        sort(r,r+n);
        for(int i=n-1;i>=0;i--){
            cout<<r[i]<<" ";
        }
        cout<<endl;
    }
}

