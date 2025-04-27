#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=200;
const int inf= 1000000;
//map<ll, list<pair<ll,ll>>> adj;
ll r[sz][sz];
bool vis[sz]={0};
//int dist[sz]={INT_MAX};

int main(void){
    //ios_base::sync_with_stdio(0);
	//cin.tie(0);
    int tst,n,m,k,q,ortst;
    while(1){
        //memset(dist,INT_MAX,sizeof(dist));
        cin>>n>>m>>q;
        if(n==0) break;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(i!=j) r[i][j]=inf;
                else r[i][j]=0;
            }
        }
        ll a,b,w,srcc;
        for(int i=0;i<m;i++){
            cin>>a>>b>>w;
            if(r[a][b]>w) r[a][b]=w;
            //addEdge(b,a,w);
        }

        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(r[i][k]<inf && r[k][j]<inf){
                        r[i][j]=min(r[i][j], r[i][k]+r[k][j]);
                        //cout<<"ok"<<r[i][j]<<endl;
                    }
                }
            }
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(r[i][j]==-inf) break;
                    if(r[k][k]<0 && r[i][k]!=inf && r[k][j]!=inf){
                        r[i][j]=-inf;
                        break;
                    }
                }
            }
        }

        while(q--){
            cin>>a>>b;
            if(r[a][b]==inf) cout<<"Impossible"<<endl;
            else if(r[a][b]==-inf) cout<<"-Infinity"<<endl;
            else cout<<r[a][b]<<endl;
        }
        cout<<endl;
    }
}
