#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=205;
bool vis[sz]={0};
map<ll, list<ll>> adj;
int color[sz]={INT_MAX};


void addEdge(ll u, ll v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

bool bfs(int x){
    queue<int> q;
    vis[x]=true;
    color[x]=0;
    q.push(x);
    //cout<<"ok";
    while(!q.empty()){
        int t=q.front();
        q.pop();
        for(auto it=adj[t].begin();it!=adj[t].end();it++){
            if(vis[*it]==0){
                vis[*it]=true;
                color[*it]=(color[t]+1)%2;
                q.push(*it);
                //cout<<*it<<" color1: "<<color[*it]<<" and "<<t<<" color2: "<<color[t]<<endl;
            }
            else{
                if(color[*it]==color[t]){
                        //cout<<*it<<" color1: "<<color[*it]<<" and "<<t<<" color2: "<<color[t]<<endl;
                    return false;}
            }
        }
    }
    return true;
}

int main(void){
    ll n,k,m,tst,ortst;
    while(1){
    cin>>n;
    if(n==0) break;
    cin>>m;
    for(int i=0;i<=sz;i++){
        vis[i]=false;
        color[i]=INT_MAX;
    }
    ll e1,e2,t,b,e;
    for(int i=0;i<m;i++){
        cin>>e1>>e2;
        addEdge(e1,e2);
    }
    bool ans= bfs(0);
    if(ans) cout<<"BICOLORABLE."<<endl;
    else cout<<"NOT BICOLORABLE."<<endl;
    adj.clear();
    }
}
