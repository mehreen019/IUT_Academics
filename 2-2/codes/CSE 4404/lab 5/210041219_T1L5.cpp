#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int sz=160;
const int inf = INT_MAX;
int dist[sz][sz];

int main(void){
    int n,m,q,a,b,w;
    while(1){
        cin>>n>>m>>q;
        if(n==0) break;

        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(i!=j) dist[i][j]= inf;
                else dist[i][j]=0;
            }
        }
        
        for(int i=0;i<m;i++){
            cin>>a>>b>>w;
            dist[a][b]= min(dist[a][b], w);
        }

        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(dist[i][k]<inf && dist[k][j]<inf){
                        dist[i][j]= min(dist[i][j], dist[i][k]+dist[k][j]);
                    }
                }
            }
        }


        while(q--){
            cin>>a>>b;
            if(dist[a][b]==inf) cout<<"Impossible"<<endl;
            else cout<<dist[a][b]<<endl;
        }
        cout<<endl;
    }
}
