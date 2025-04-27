#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxx=200005;

bool vis[maxx]={0};
map<ll, list<ll>> adj;
ll money[maxx]={0};
ll ans=0,cou=0;

void addEdge(ll u, ll v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void dfs(ll n){
    if(vis[n]!=0) return;
    //else if(adj[n].empty()){ return;}

    vis[n]=true;
    ans+= money[n];
    cou++;

    for(auto it=adj[n].begin();it!=adj[n].end();it++){
        if(vis[*it]==0){
            dfs(*it);
        }
    }
}

int main(void){
    int tst,n,k,ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){
        cou=0; ans=0;
        bool found=true, fs=true;
        ll mainans;
        cin>>n>>k;
        for(int i=0;i<=n+3;i++){
            vis[i]=false;
            money[i]=0;
        }
        for(int i=1;i<=n;i++){
            cin>>money[i];
        }
        ll e1,e2,t,b,e;
        for(int i=0;i<k;i++){
            cin>>e1>>e2;
            addEdge(e1,e2);
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                dfs(i);
                //cout<<ans<<" "<<cou<<endl;
                double c=(double)ans/cou;
                if(c!=(int)c){ found=false; break;}

                if(fs){ mainans=(int)c; fs=false; }
                else{
                    int tt= (int)c;
                    if( tt != mainans){
                        found=false; break;
                    }
                }
                ans=0; cou=0;
            }
        }
        cout<<"Case "<<ortst-tst<<": ";
        if(found) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;

        for(int i=0;i<=n;i++){
            adj[i].clear();
        }
    }
    /*float c=15.00/2.00;
    if(c==(int)c) cout<<"yes"<<endl;
    else cout<<"no"<<endl;*/
}
