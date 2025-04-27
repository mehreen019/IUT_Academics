#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX=100005;
int parent[MAX];
int ans=-1;

///set each nodes parent to itself
void make_set(int v) {
    parent[v] = v;
}

///find parent of a value by following it's chain upwards
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

///find parents, and if they don't match, set one's parent to another's
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        {
            parent[b] = a;
        }
}

int main(void){
    int n,q,a,b;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        make_set(i);
    }
    while(q--){
        cin>>a>>b;
        int pa=find_set(a);
        int pb=find_set(b);
        if(pa!=pb){
            union_sets(a,b);
        }
    }
}
