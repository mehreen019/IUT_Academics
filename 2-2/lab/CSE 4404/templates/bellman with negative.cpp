#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXX=30005;
//const int large= INT_MAX;
const ll large=LLONG_MAX;
map<ll, list<pair<int,int> > > adj;
vector< vector<int>> edges;
ll dist[MAXX];
ll parent[MAXX];
bool vis[MAXX];
int x;

void addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
    edges.push_back({u,v,w});
    //adj[v].push_back({u,w});
}

int bellman(ll src, ll n){

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
    bool a=false;

    for(int i=0;i<n;i++){
        for (auto &edge : edges)
        {
            ll u = edge[0];
            ll v = edge[1];
            ll w = edge[2];

            //cout<<u<<" "<<v<<" "<<w<<" before dist is: "<<dist[v]<<endl;
                if(dist[v] > dist[u] + w){
                    //cout<<u<<" "<<v<<" "<<w<<" before dist is: "<<dist[v]<<endl;
                    dist[v] =  dist[u] + w;
                    parent[v]= u;
                    a=true;
                    x=v;
                }
        }
    }

    return a;
}

int main(void){
        int n,m,e1,e2,w;
        cin>>n>>m;

        for(int i=0;i<MAXX;i++){
            dist[i]= 0;
            //parent[i].push(i);
            parent[i]=-1;
            vis[i]=0;
        }

        for(int i=1;i<=m;i++){
            cin>>e1>>e2>>w;
            addEdge(e1,e2,w);
        }
        bool ans;
        ans= bellman(1,n);
        //a=bellman(1,n);
        /*for(int i=1;i<=n;i++){
            cout<<i<<" and parent: "<<parent[i]<<endl;
        }*/
        //cout<<a<<endl;
        //bellman(0,n);
        if(ans){
            cout<<"YES"<<endl;
            int k=x;
            stack<ll> p;
            map<ll,ll> cnt;
            cnt[k]=0;
            /*for(int i=1;i<=n;i++){
                cout<<i<<" and parent: "<<parent[i]<<endl;
            }*/
            while(1){
                cnt[k]++;
                if(cnt[k]==2) break;
                k=parent[k];
            }
            cnt.clear();
            while(cnt[k]<1){
                cnt[k]++;
                p.push(k);
                k=parent[k];
            }
            //p.push(k);
            cout<<parent[p.top()]<<" ";
            //k=p.top();
            while(!p.empty()){
                cout<<p.top()<<" ";
                p.pop();
            }
            //cout<<k<<endl;
        }
        else cout<<"NO"<<endl;

        edges.clear();
        adj.clear();
}


//YES
//1 3 12 14 23 25 34 36 45 47 56 58 67 77 78 87 89 1
