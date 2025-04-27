#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define tie ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
ll INF=1e18;

map<ll, list<ll>> adj;

void addEdge(ll u, ll v){
    adj[u].push_back(v);
}

void dfs(ll n, int* visit){
    //if(visit[n]!=0) return;

    visit[n]++;

    for(auto it=adj[n].begin();it!=adj[n].end();it++){
        if(!visit[*it]) dfs(*it,visit);
    }
}

int main(void){
    ll n,m,e1,e2;
    cin>>n>>m;
    bool in[n+1]={0};
    for(int i=0;i<m;i++){
        cin>>e1>>e2;
        addEdge(e1,e2);
        in[e1]=1;
    }
    int visit[n+1]={0};
    dfs(1, visit);
    for(int j=2;j<=n;j++){
        if(!visit[j]){
            cout<<"NO"<<endl<<1<<" "<<j<<endl;
            return 0;
        }
    }

    cout<<"YES"<<endl;
}
