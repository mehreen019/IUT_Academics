#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXX = 200005;
map<string, list<pair<string,ll>>> adj;
//vector<vector<pair<string,ll> > > adj(MAXX);
map<string, ll> dist;
map<string, bool> vis;

void addEdge(string u, string v, int w){
    adj[u].push_back({v,w});
}

ll djikstra(string k){
    priority_queue<pair<ll,string>, vector<pair<ll,string> >, greater<pair<ll,string> > > pq;
    pq.push({0,k});
    ll totalCount=0;
    while(!pq.empty()){
        pair<ll, string> cur = pq.top();
        pq.pop();
        string node = cur.second;
        ll weight = cur.first;

        if(vis[node]==1) continue;
        else vis[node]=1;
        totalCount+=weight;

        for(auto &it: adj[node]){
        //int sz= adj[node].size();
        //for(int i=0;i<sz;i++){
            ll dw= it.second;
            string dn= it.first;
            if(vis[dn]!=1){
                pq.push({dw,dn});
            }
        }
    }
    return totalCount;
}

int main(void){
    int tst,ortst;
    cin>>tst;
    ortst=tst;

while(tst--){
    cin.ignore();
    int m;
    cin>>m;
    string e1,e2;
    ll w, cou=0;
    set<string> st;
    for(int i=0;i<m;i++){
        cin>>e1>>e2>>w;
        addEdge(e1,e2,w);
        dist[e1]=INT_MAX;
        vis[e1]=0;
        st.insert(e1);

        addEdge(e2,e1,w);
        dist[e2]=INT_MAX;
        vis[e2]=0;
        st.insert(e2);
    }
    bool ans = 1;
    /*for(auto &it1: st){
        djikstra(it1);
        for(auto it:dist){
            if(it.second==INT_MAX){ ans=0; break;}
            else{ ans=1; cou+=it.second;}
        }

        if(!ans) break;
        else{
            tc=min(tc, cou);
            cout<<it1<<" as source: "<<cou<<endl;
            cou=0;
            for(auto it:dist){
                it.second=INT_MAX;
            }
        }
    }*/
    cou = djikstra(e1);
    for(auto it:vis){
        if(!it.second){ ans=0; break;}
        //else{ ans=1; cou+=it.second;}
    }
    cout<<"Case "<<ortst-tst<<": ";
    if(ans){ cout<<cou<<endl; }
    else cout<<"Impossible"<<endl;

    dist.clear();
    vis.clear();
    adj.clear();
}
}


