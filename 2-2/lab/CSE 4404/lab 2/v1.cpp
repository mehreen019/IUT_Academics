#include<bits/stdc++.h>
using namespace std;
int main(void){
    int tst,n;
    cin>>tst;
    while(tst--){
        cin>>n;
        int r[n];
        for(int i=0;i<n;i++){
            cin>>r[i];
        }
        sort(r,r+n);
        bool ans=1;
        for(int i=1;i<n;i++){
            if(r[i]<=r[i-1]){ ans=0; break; }
        }
        if(ans){
            cout<<"YES"<<endl;
        }
        else cout<<"NO"<<endl;
    }
}
