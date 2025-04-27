#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXX = 200005;
//map<ll, list<pair<ll,ll>>> adj;
vector<vector<pair<ll,ll> > > adj(MAXX);
int dist[MAXX];
bool vis[MAXX];
int all=0;
set<ll> secSmall;

void addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
}

void djikstra(int k){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > pq;
    pq.push({0,k});
    dist[k]=0;
    int cou=0;
    while(!pq.empty()){
        pair<ll,ll> cur = pq.top();
        pq.pop();
        ll node = cur.second;
        ll weight = cur.first;

        if(vis[node]==1) continue;
        else vis[node]=1;
        //cou++;

        //for(auto &it =adj[node].begin(); it!=adj[node].end(); it++){
        int sz= adj[node].size();
        for(int i=0;i<sz;i++){
            ll dw= adj[node][i].second, dn= adj[node][i].first;
            if(dn==all){ secSmall.insert(dist[dn]); secSmall.insert(dist[node] + dw);}
            //cout<<"to visit: "<<dn<<" from: "<<node<<" and dist is: "<<dist[dn]<<endl;
            if(dist[dn] > dist[node] + dw){
                dist[dn] = dist[node] + dw;
                pq.push({ dist[dn], dn});
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
    }

    int n,m;
     cin>>n>>m;
     all=n;

    int e1,e2,w,q,idx;
    for(int i=0;i<m;i++){
        cin>>e1>>e2>>w;
        addEdge(e1,e2,w);
        addEdge(e2,e1,w);
    }
    djikstra(1);
    cout<<"Case "<<ortst-tst<<": "<<endl;
    /*for(int i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    }
    cout<<endl;*/
    secSmall.insert(dist[n]*3);
    set<ll>::iterator it=secSmall.begin();
    it++;
    //for(it=secSmall.begin(); it!=secSmall.end(); it++){
        cout<<*it;
    //}
    cout<<endl;
    for(int i=0;i<=n;i++){
        adj[i].clear();
    }
    secSmall.clear();
    }
}


