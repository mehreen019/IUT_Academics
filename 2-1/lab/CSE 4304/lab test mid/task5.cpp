#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(void){
    priority_queue<pair<ll, pair<ll,ll>>>pq;
    ll n,k,x,y,mul;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>x>>y;
        mul=x*y;
        pq.push({mul, {y,x}});
    }
    ll cou=0,pl=INT_MAX,ans=INT_MIN;
    while(k--){
        auto temp=pq.top();
        auto t=temp.second;
        pl=min(pl, t.first);
        cou+=t.second;
        mul=cou*pl;
        ans=max(ans, mul);
        pq.pop();
    }
    cout<<ans<<endl;
}
