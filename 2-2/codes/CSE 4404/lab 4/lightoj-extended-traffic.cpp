#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXX=205;
vector<vector<pair<int,int> > > adj(MAXX);
int dist[MAXX];
bool vis[MAXX];
bool flag[MAXX];

void addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
}

void dfs(int k){
    flag[k]=1;
    for(auto it:adj[k]){
        if(!flag[it.first]) dfs(it.first);
    }
}

void spfa(int k, int n){
    priority_queue<pair<ll,ll> > pq;
    int cnt[MAXX]={0};
    pq.push({0,k});
    dist[k]=0;
    cnt[k]++;
    while(!pq.empty()){
        pair<ll,ll> cur = pq.top();
        pq.pop();
        int node = cur.second;
        int weight = cur.first;
        vis[node]=0;

        //for(auto &it =adj[node].begin(); it!=adj[node].end(); it++){
        int sz= adj[node].size();
        for(int i=0;i<sz;i++){
            int dw= adj[node][i].second, dn= adj[node][i].first;
            //cout<<"to visit: "<<dn<<" from: "<<node<<" and dist is: "<<dist[dn]<<endl;
            if(dist[dn] > dist[node] + dw){
                dist[dn] = dist[node] + dw;

                if(vis[dn]==1) continue;
                vis[dn]=1;
                pq.push({ dist[dn], dn});
                cnt[dn]++;
                if(cnt[dn]>=n){
                    dfs(dn);
                    return;
                }

            }
        }
    }
}


int main(void){
    int tst, ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){

    for(int i=0;i<MAXX;i++){
        dist[i]= INT_MAX;
        vis[i]=0;
        flag[i]=0;
    }

    int n,m;
     cin>>n;

    int r[n+1];
    for(int i=1;i<=n;i++){
        cin>>r[i];
    }
    cin>>m;
    int e1,e2,w,q,idx;
    for(int i=0;i<m;i++){
        cin>>e1>>e2;
        w=pow((r[e2]-r[e1]), 3);
        addEdge(e1,e2,w);
        //addEdge(e2,e1,w);
    }
    spfa(1,n);
    cout<<"Case "<<ortst-tst<<": "<<endl;
    cin>>q;
    while(q--){
        cin>>idx;
        if(dist[idx]==INT_MAX || dist[idx]<3){
            cout<<"?"<<endl;
        }
        else cout<<dist[idx]<<endl;
    }

    for(int i=0;i<=n;i++){
        adj[i].clear();
    }

    }
}

