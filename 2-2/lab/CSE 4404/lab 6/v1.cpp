#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXX = 200005;
map<ll, list<pair<ll,ll>>> adj;
//vector<vector<pair<string,ll> > > adj(MAXX);
bool vis[MAXX];

void addEdge(ll u,ll v, int w){
    adj[u].push_back({v,w});
}

ll prim(ll k){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > pq;
    pq.push({0,k});
    ll totalCount=0;
    while(!pq.empty()){
        pair<ll, ll> cur = pq.top();
        pq.pop();
        ll node = cur.second;
        ll weight = cur.first;

        if(vis[node]==1) continue;
        else vis[node]=1;
        totalCount+=weight;

        for(auto &it: adj[node]){
        //int sz= adj[node].size();
        //for(int i=0;i<sz;i++){
            ll dw= it.second;
            ll dn= it.first;
            if(vis[dn]!=1){
                pq.push({dw,dn});
            }
        }
    }
    return totalCount;
}

int main(void){
while(1){
    int n,m,e1,e2,w;
    cin>>n>>m;
    if(n==0) break;
    int cou=0, inc=0;
    for(int i=0;i<n;i++){
        vis[i]=0;
    }
    for(int i=1;i<=m;i++){
        cin>>e1>>e2>>w;
        inc+=w;
            //cout<<"ok";
        addEdge(e1,e2,w);
        addEdge(e2,e1,w);
    }
    bool ans = 1;
    cou = prim(0);
    cout<<inc-cou<<endl;

    adj.clear();
}
}


