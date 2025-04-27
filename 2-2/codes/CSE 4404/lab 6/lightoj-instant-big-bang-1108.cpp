#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXX=100005;
const int large= INT_MAX;
//const ll large=LLONG_MAX;
map<int, list<pair<int,int> > > adj;
vector< vector<int>> edges;
ll dist[MAXX]={INT_MAX};
bool vis[MAXX]={0};
vector<int> ans;

void addEdge(int u, int v, int w){
    adj[v].push_back({u,w});
    edges.push_back({v,u,w});
}

void dfs(int k){
    vis[k]=1;
    ans.push_back(k);
    //cout<<k<<" ";
    for(auto &it: adj[k]){
        if(!vis[it.first]) dfs(it.first);
    }
}

void bellman(int src, int n){

    dist[src]=0;

    for(int i=0;i<n;i++){
        for (auto &edge : edges)
        {
            ll u = edge[0];
            ll v = edge[1];
            ll w = edge[2];

             if(dist[v] > dist[u] + w){
                    dist[v] =  dist[u] + w;
             }
        }
    }

        for (auto &edge : edges)
        {
            ll u = edge[0];
            ll v = edge[1];
            ll w = edge[2];

            //cout<<u<<" "<<v<<" "<<w<<" before dist is: "<<dist[v]<<endl;
                if(dist[v] > dist[u] + w){
                    dist[v] =  dist[u] + w;
                    //cout<<u<<" "<<v<<" "<<w<<" after dist is: "<<dist[v]<<endl;
                        if(!vis[u]){
                            //cout<<u<<endl;
                            dfs(u);
                        }
                // }
                }
        }
}



int main(void){
    int tst,ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){
        cin.ignore();
        int n,m,e1,e2,w;
        cin>>n>>m;

        for(int i=0;i<=n;i++){
            dist[i]= large;
            vis[i]=0;
        }

        for(int i=1;i<=m;i++){
            cin>>e1>>e2>>w;
            addEdge(e1,e2,w);
        }
        bellman(0,n);
        cout<<"Case "<<ortst-tst<<": ";
        if(ans.size()==0){
            cout<<"impossible";
        }
        else{
            sort(ans.begin(), ans.end());
            for(auto it: ans){
                cout<<it<<" ";
            }
        }
        cout<<endl;

        adj.clear();
        ans.clear();
        edges.clear();
    }
}
