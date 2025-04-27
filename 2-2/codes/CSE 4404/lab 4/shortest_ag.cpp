#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=2000005;
map<ll, list<pair<int,int>>> adj;
ll dist[sz]={INT_MAX};

void addEdge(ll u, ll v,ll w){
    adj[u].push_back({v,w});
    //adj[v].push_back({u,w});
}

void djikstra(ll src){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[src]=0;
    pq.push({0,src});
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
       // cout<<dist[cur.second]<<" ";
        for(auto &it: adj[cur.second]){
            cout<<"to visit: "<< it.first <<" from: "<< cur.second <<" and dist is: "<<dist[it.second]<<endl;
            if(dist[it.first]> dist[cur.second]+ it.second){
                dist[it.first]= dist[cur.second]+ it.second;
                pq.push({dist[it.first], it.first});
            }
        }
    }
}

int main(void){
    for(int i=0;i<sz;i++){
        dist[i]= INT_MAX;
        //vis[i]=0;
    }

    int n,m;
    cin>>n>>m;
    int e1,e2,w;
    for(int i=0;i<m;i++){
        cin>>e1>>e2>>w;
        addEdge(e1,e2,w);
    }
    djikstra(1);
    for(int i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    }
}
