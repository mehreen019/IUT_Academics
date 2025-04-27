#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXX=1009;
const ll large=INT_MAX;
ll dist[MAXX];

ll mst(int src, string s){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    //priority_queue<int> pq;
    pq.push({0,src});
    ll minCost=0;
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        //if(cur.first == large) continue;
        if(s[cur.second]=='0'){ minCost+=cur.first; s[cur.second]='1';}

        ll ld,rd;
        //cout<<"from: "<<cur.second<<" to: "<<cur.second-1<<endl;
        if(cur.second-1 >=0 && s[cur.second-1]=='0'){
                if(dist[cur.second-1]>dist[cur.second])
                    ld=dist[cur.second-1] - dist[cur.second];
                else ld=dist[cur.second] - dist[cur.second-1];
        }
        else ld=large;

        if(cur.second+1 < s.size() && s[cur.second+1]=='0'){
            if(dist[cur.second+1]>dist[cur.second])
                    rd=dist[cur.second+1] - dist[cur.second];
                else rd=dist[cur.second] - dist[cur.second+1];
        }
        else rd=large;

        if(ld < large){
            pq.push({ld, cur.second-1});
            //cout<<"from: "<<cur.second<<" to: "<<cur.second-1<<" dist is:"<<ld<<endl;
        }
        if(rd < large){
            pq.push({rd, cur.second+1});
            //cout<<"from: "<<cur.second<<" to: "<<cur.second+1<<"dist is:"<<rd<<endl;
        }
    }

    return minCost;
}

int main(void){
    int tst;
    cin>>tst;
    while(tst--){
        int n;
        cin>>n;

        for(int i=0;i<=n;i++){
            dist[i]=INT_MAX;
        }

        string s;
        int idx;
        cin>>s;
        for(int i=0;i<n;i++){
            cin>>dist[i];
            if(s[i]=='1') idx=i;
        }
        ll ans = mst(idx,s);
        cout<<ans<<endl;
    }
}
