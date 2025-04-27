#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=2e5 + 5;
//map<ll, list<pair<ll,ll>>> adj;
priority_queue<ll> pqMax[sz];
vector<vector<pair< int,int> > >adj(sz);

void addEdge(int u, int v,int w){
    adj[u].push_back({v,w});
    //adj[u] = {v,w};
    //cout<<"ok";
}

int main(void){
    int tst, ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){
        int n,m;
        cin>>n>>m;
        int e1,e2,w,q,idx;
        for(int i=0;i<m;i++){
            cin>>e1>>e2>>w;

            addEdge(e1,e2,w);
            addEdge(e2,e1,w);
        }

        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        pqMax[1].push(0);
        pq.push({0,1});
        int k=2;
        while(!pq.empty()){
            auto cur=pq.top();
            pq.pop();

            if(cur.first > pqMax[cur.second].top()) continue;
            for(auto &it: adj[cur.second]){
                ll temp = cur.first + it.second;
                if(pqMax[it.first].size()<k){
                    pqMax[it.first].push(temp);
                    pq.push({temp, it.first});
                }
                else if(pqMax[it.first].top() > temp){
                    pqMax[it.first].pop();
                    pqMax[it.first].push(temp);
                    pq.push({temp, it.first});
                }
            }
        }
        ll ans=pqMax[n].top();
        //cout<<"ok";
        //shortest(1,n);
        cout<<"Case "<<ortst-tst<<": "<<ans<<endl;
        //adj.clear();
        for(int i=0;i<=n+2;i++){
            pqMax[i] = priority_queue<ll>();
            adj[i].clear();
        }
    }
}
