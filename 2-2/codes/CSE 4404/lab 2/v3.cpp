#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(void){
    ll tst,n;
    cin>>tst;
    while(tst--){
        cin>>n;
        ll arr[n], cp[n];
        vector<pair<int,int>>r;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            cp[i]=arr[i];
            r.push_back({arr[i],i});
        }
        sort(r.begin(),r.end());
        reverse(r.begin(),r.end());
        int j=0,k=n-1,a,b,c;
        bool ans=0;
        for(int i=0;i<n;i++){
            while(j<k){
                if(r[i].first>cp[j] && r[i].first>cp[k]){
                    ans=1;
                    a=j+1;
                    b=r[i].second+1;
                    c=k+1;
                    break;
                }
                else{
                    if(r[i].first<=cp[j]) j++;
                    if(r[i].first<=cp[k]) k--;
                    break;
                }
            }
            if(ans) break;
        }
        if(ans){
            cout<<"YES"<<endl<<a<<" "<<b<<" "<<c<<endl;

        }
        else cout<<"NO"<<endl;
    }
}
