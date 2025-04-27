#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=200005;
map<ll, list<pair<ll,ll>>> adj;
priority_queue<ll> pqMax[sz];

void addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
}

void djikstra(ll src, ll k){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    pq.push({0,src});
    pqMax[src].push(0);
    while(!pq.empty()){
        auto cur = pq.top();
        pq.pop();

        if(pqMax[cur.second].top() < cur.first) continue;
        for(auto &it: adj[cur.second]){
            int temp = cur.first + it.second;
            if(pqMax[it.first].size() < k){
                pqMax[it.first].push(temp);
                pq.push({temp, it.first});
            }
            else if(pqMax[it.first].top()>temp){
                pqMax[it.first].pop();
                pqMax[it.first].push(temp);
                pq.push({temp, it.first});
            }
        }
    }
}

int main(void){
    int n,m,k,a,b,w;
    cin>>n>>m>>k;
    for(int i=0;i<m;i++){
        cin>>a>>b>>w;
        addEdge(a,b,w);
    }
    djikstra(1,k);
    stack<int> ans;
    while(!pqMax[n].empty()){
        ans.push(pqMax[n].top());
        pqMax[n].pop();
    }
    while(!ans.empty()){
        cout<<ans.top()<<" ";
        ans.pop();
    }
    cout<<endl;
}
