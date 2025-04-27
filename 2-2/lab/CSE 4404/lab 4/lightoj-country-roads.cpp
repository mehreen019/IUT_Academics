#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=200005;
map<ll, list<pair<int,int>>> adj;
int dist[sz]={INT_MAX};
bool vis[sz]={0};

void addEdge(ll u, ll v,ll w){
    adj[u].push_back({v,w});
}

void shortest(ll src){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[src]=0;
    pq.push({0,src});
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();

        //if(vis[cur.second]) continue;
        //else vis[cur.second]=1;

       // cout<<dist[cur.second]<<" ";
        for(auto &it: adj[cur.second]){
            int maxCost=max(dist[cur.second], it.second);
            if(dist[it.first]> maxCost){
                dist[it.first]= maxCost;
                pq.push({dist[it.first], it.first});
            }
        }
    }
}

int main(void){
    int tst,n,m,q,ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){
        cin.ignore();
        for(int i=0;i<sz;i++){
            dist[i]=INT_MAX;
            vis[i]=0;
        }
        //memset(dist,INT_MAX,sizeof(dist));
        cin>>n>>m;
        int a,b,w,srcc;
        for(int i=0;i<m;i++){
            cin>>a>>b>>w;
            addEdge(a,b,w);
            addEdge(b,a,w);
        }
        cin>>srcc;
        shortest(srcc);
        cout<<"Case "<<ortst-tst<<": "<<endl;
        for(int i=0;i<n;i++){
            if(dist[i]==INT_MAX){
                cout<<"Impossible"<<endl;
            }
            else{
                cout<<dist[i]<<endl;
            }
        }
        adj.clear();
    }

}
