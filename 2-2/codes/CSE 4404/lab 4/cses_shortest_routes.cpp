#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXX = 200005;
//map<ll, list<pair<ll,ll>>> adj;
vector<vector<pair<ll,ll> > > adj(MAXX);
ll parent[MAXX];
ll dist[MAXX];
bool vis[MAXX];

void addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
}

void djikstra(int k){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > pq;
    pq.push({0,k});
    dist[k]=0;
    while(!pq.empty()){
        pair<ll,ll> cur = pq.top();
        pq.pop();
        ll node = cur.second;
        ll weight = cur.first;

        if(vis[node]==1) continue;
        else vis[node]=1;

        //for(auto &it =adj[node].begin(); it!=adj[node].end(); it++){
        int sz= adj[node].size();
        for(int i=0;i<sz;i++){
            ll dw= adj[node][i].second, dn= adj[node][i].first;
            //cout<<"to visit: "<<dn<<" from: "<<node<<" and dist is: "<<dist[dn]<<endl;
            if(dist[dn] > dist[node] + dw){
                dist[dn] = dist[node] + dw;
                pq.push({ dist[dn], dn});
            }
        }
    }
}

int main(void){

    for(int i=0;i<MAXX;i++){
        parent[i]=-1;
        dist[i]= LLONG_MAX;
        vis[i]=0;
    }

    int n,m;
    cin>>n>>m;
    int e1,e2,w;
    for(int i=0;i<m;i++){
        cin>>e1>>e2>>w;
        addEdge(e1,e2,w);
        //addEdge(e2,e1,w);
    }
    djikstra(1);
    for(int i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    }
}


