#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXX=1000000;
const int large= INT_MAX;
//const ll large=LLONG_MAX;
map<int, list<pair<int,int> > > adj;
ll dist[MAXX]={INT_MAX};
bool vis[MAXX]={0};
set<int> ans;

void addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
}

void dfs(int k){
    vis[k]=1;
    ans.insert(k);
    cout<<k<<" ";
    for(auto &it: adj[k]){
        if(!vis[it.first]) dfs(it.first);
    }
}

bool bellman(int src, int n){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    //priority_queue<int> pq;
    vector<int> cnt(n,0);
    dist[src]=0;
    pq.push({0,src});
    //parent[src].push(src);

    ll minCost=0;
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();

        //if(vis[cur.second]==1) continue;
        //else vis[cur.second]=1;

        for(auto &it : adj[cur.second]){

            if(dist[it.first] > dist[cur.second]+it.second){
                dist[it.first] = dist[cur.second]+it.second;
                //parent[it.first].push(cur.second);//;
                pq.push({dist[it.first], it.first});
                cnt[it.first]++;


                if(cnt[it.first]>=n){
                    return true;
                }
            }
        }
    }
    return false;
}

int main(void){
    int tst,ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){
        int n,m,e1,e2,w;
        cin>>n>>m;

        for(int i=0;i<=n;i++){
            dist[i]=INT_MAX;
            //parent[i].push(i);
            vis[i]=0;
        }

        for(int i=1;i<=m;i++){
            cin>>e1>>e2>>w;
            //cout<<"ok";
            addEdge(e1,e2,w);
        }
        bool ans = bellman(0,n);
        if(ans) cout<<"possible"<<endl;
        else cout<<"not possible"<<endl;

        adj.clear();
    }
}
