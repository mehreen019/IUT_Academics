#include<bits/stdc++.h>
using namespace std;
const int MAXX=200005;
int parent[MAXX];
int largest[MAXX];
int connected=0, lc=-1;

void makeSet(int n){
    for(int i=0;i<=n;i++){
        parent[i]=i;
        largest[i]=1;
    }
    connected=n;
}

int findPar(int k){
    if(parent[k]!=k) return parent[k]=findPar(parent[k]) ;
    else return k;
}

void unionset(int a, int b){
    int pa= findPar(a);
    int pb= findPar(b);
    connected--;
    if(largest[pa]>largest[pb]){
        parent[pb]=pa;
        largest[pa]+=largest[pb];
        lc=max(lc, largest[pa]);
        return;
    }
    else{
        parent[pa]=pb;
        largest[pb]+=largest[pa];
        lc=max(lc, largest[pb]);
        return;
    }

}



int main(void){
    int n,m,a,b,ans;
    cin>>n>>m;
    makeSet(n);
    while(m--){
        cin>>a>>b;
        int pa= findPar(a);
        int pb= findPar(b);
        if(pa!=pb){
            unionset(a,b);
        }
        cout<<connected<<" "<<lc<<endl;
    }
}
