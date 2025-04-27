#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX=100005;
int parent[MAX];
int connected=0;
int largest[MAX];
int ans=-1;

void make_set(int v) {
    parent[v] = v;
    largest[v]=1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        {   if(largest[a]<largest[b]){
                swap(largest[a],largest[b]);
            }
            parent[b] = a;
            largest[a]+=largest[b];
            //cout<<b<<"ok"<<largest[b]<<endl;
        }
    ans=max(ans, largest[a]);
    connected--;
}

int main(void){
    int n,q,a,b;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        make_set(i);
    }
    connected=n;
    while(q--){
        cin>>a>>b;
        int pa=find_set(a);
        int pb=find_set(b);
        if(pa!=pb){
            union_sets(a,b);
        }
        cout<<connected<<" "<<ans<<endl;
    }
}
