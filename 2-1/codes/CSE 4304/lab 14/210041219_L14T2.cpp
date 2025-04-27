#include<bits/stdc++.h>
using namespace std;
const int MAX=1001;
int parent[MAX];

void make_set(int v) {
    parent[v] = v;
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
        parent[b] = a;
}

int main(void){
    int n,a,b,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        make_set(i);
    }
    vector<pair<int,int>>v;
    vector<pair<int,int>>nw;
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        int pa=find_set(a);
        int pb=find_set(b);
        if(pa!=pb){
            union_sets(a,b);
        }
        else{
            v.push_back({a,b});
        }
    }
    int pa=find_set(1);
    for(int i=2;i<=n;i++){
        int pb=find_set(i);
        if(pa!=pb){
            nw.push_back({1,i});
            union_sets(1,i);
        }
    }
    cout<<nw.size()<<endl;
    for(int i=0;i<nw.size();i++){
        cout<<v[i].first<<" "<<v[i].second<<" "<<nw[i].first<<" "<<nw[i].second<<endl;
    }
}
