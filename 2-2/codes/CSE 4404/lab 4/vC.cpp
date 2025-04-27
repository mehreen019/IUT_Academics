#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXX = 200005;
map<ll, list<pair<ll,ll>>> adj;
//vector<vector<pair<string,ll> > > adj(MAXX);
map<ll, ll> dist;
map<ll, bool> vis;

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
    int n,tst,ortst;
    cin>>tst;
    ortst=tst;

while(tst--){
    cin.ignore();
    int m;
    cin>>n;
    ll w, cou=0, inc=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>w;
            if(w!=0){
            addEdge(i,j,w);
            addEdge(j,i,w);
            inc+=w;
            }
            dist[i]=INT_MAX;
            vis[i]=0;
            //addEdge(j,i,w);
            dist[j]=INT_MAX;
            vis[j]=0;
        }
    }
    bool ans = 1;
    cou = prim(0);
    for(auto it:vis){
        if(!it.second){ ans=0; break;}
        //else{ ans=1; cou+=it.second;}
    }
    cout<<"Case "<<ortst-tst<<": ";
    if(ans){ cout<<inc-cou<<endl; }
    else cout<<-1<<endl;

    dist.clear();
    vis.clear();
    adj.clear();
}
}


