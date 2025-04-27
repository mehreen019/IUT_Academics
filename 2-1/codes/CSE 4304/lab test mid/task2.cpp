#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,q,x,cou=0;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>x;
        cou+=x;
        arr[i]=cou;
    }
    cin>>q;
    while(q--){
        cin>>x;
        int l=0,r=n-1,ans=0,m;
        while(l<r){
            m=(l+(r))/2;
            //cout<<l<<" "<<r<<" "<<m<<endl;
            if((x>arr[m-1] && x<arr[m]) || arr[m]==x){
                ans=m;
                break;
            }
            else if(x<arr[m]){
                r=m;
            }
            else l=m+1;

        }
        if(ans!=0) cout<<ans+1<<endl;
        else cout<<l+1<<endl;
    }
}
//2 9 12 16 25
