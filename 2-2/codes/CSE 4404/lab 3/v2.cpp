#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=200005;
bool vis[sz]={0};
map<ll, list<ll>> adj;
int dist[sz]={INT_MAX};
int parent[sz]={INT_MAX};

void addEdge(ll u, ll v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void bfs(int x){
    queue<int> q;
    vis[x]=true;
    dist[x]=0;
    q.push(x);
    while(!q.empty()){
        int t=q.front();
        q.pop();
        for(auto it=adj[t].begin();it!=adj[t].end();it++){
            if(vis[*it]==0){
                vis[*it]=true;
                q.push(*it);
                dist[*it]=dist[t]+1;
                parent[*it]=t;
            }
        }
    }
}

int main(void){
    ll n,k,tst,ortst;
    cin>>n>>k;
    for(int i=0;i<=n;i++){
        vis[i]=false;
        dist[i]=INT_MAX;
    }
    ll e1,e2,t,b,e;
    for(int i=0;i<k;i++){
        cin>>e1>>e2;
        addEdge(e1,e2);
    }
    bfs(1);
    if(dist[n]==INT_MAX){
        cout<<"IMPOSSIBLE"<<endl;
    }
    else{
        cout<<dist[n]+1<<endl;
        int temp=n;
        stack<int> st;
        while(temp!=1){
            st.push(temp);
            temp=parent[temp];
        }
        cout<<1<<" ";
        while(!st.empty()){
            cout<<st.top()<<" ";
            st.pop();
        }
    }
}
