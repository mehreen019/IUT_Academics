#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXX=30005;
//const int large= INT_MAX;
const ll large=LLONG_MAX;
map<ll, list<pair<int,int> > > adj;
ll dist[MAXX];
ll parent[MAXX];
bool vis[MAXX];

void addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
    //adj[v].push_back({u,w});
}

int bellman(ll src, ll n){
    /*for(int i=0;i<=n;i++){
        dist[i]=INT_MAX;
        vis[i]=0;
    }*/

    //cout<<"ok"<<endl;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    //priority_queue<int> pq;
    vector<ll> cnt(n+5);
    fill(cnt.begin(), cnt.end(), 0);
    dist[src]=0;
    pq.push({0,src});
    //parent[src].push(src);

    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();

        //if(vis[cur.second]==1) continue;
        //else vis[cur.second]=1;

        for(auto &it : adj[cur.second]){

                cout<<"before idx: "<<it.first<<" dist: "<<dist[it.first]<<endl;
                ll l= dist[it.first];
                ll r= dist[cur.second] + it.second;
            if(l > r){
                dist[it.first] = r;
                parent[it.first]= cur.second;//;
                pq.push({dist[it.first], it.first});
                cnt[it.first]++;
                cout<<"after idx: "<<it.first<<" dist: "<<dist[it.first]<<endl;

                if(cnt[it.first]>=n){
                    //dist[it.first]=-1;
                    cout<<"src:"<<cur.second<<" dist: "<<dist[it.first]<<endl;
                    //if(!vis[cur.second])  dfs(cur.second);
                    /*for(int i=1;i<=n;i++){
                        cout<<i<<" and parent: "<<parent[i]<<endl;
                    }

                    cout<<it.first<<endl;*/
                    return it.first;
                }
            }
        }
    }
    return -1;
}

int main(void){
        int n,m,e1,e2,w,pls=-1;
        cin>>n>>m;

        for(int i=0;i<MAXX;i++){
            dist[i]= large;
            //parent[i].push(i);
            parent[i]=i;
            vis[i]=0;
        }

        for(int i=1;i<=m;i++){
            cin>>e1>>e2>>w;
            addEdge(e1,e2,w);
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                pls = bellman(i,n);
                vis[i]=1;
                //cout<<pls<<endl;
            }
            if(pls!=-1) break;
        }
        //a=bellman(1,n);
        /*for(int i=1;i<=n;i++){
            cout<<i<<" and parent: "<<parent[i]<<endl;
        }*/
        //cout<<a<<endl;
        //bellman(0,n);
        if(pls!=-1){
            cout<<"YES"<<endl;
            int k=pls;
            stack<ll> p;
            map<ll,ll> cnt;
            cnt[k]=0;
            while(cnt[k]<1){
                cnt[k]++;
                p.push(k);
                k=parent[k];
            }
            //p.push(k);
            //cout<<k<<" ";
            k=p.top();
            while(!p.empty()){
                cout<<p.top()<<" ";
                p.pop();
            }
            cout<<k<<endl;
        }
        else cout<<"NO"<<endl;


        adj.clear();
}


//YES
//1 3 12 14 23 25 34 36 45 47 56 58 67 77 78 87 89 1
