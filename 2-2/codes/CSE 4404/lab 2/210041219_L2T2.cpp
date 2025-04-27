#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n;
    cin>>n;
    int start[n], endd[n],idx=INT_MIN;
    for(int i=0;i<n;i++){
        cin>>start[i];
    }
    for(int i=0;i<n;i++){
        cin>>endd[i];
        idx=max(idx, endd[i]);
    }
    vector<bool> vis(idx,0);
    vector<pair<int, int>> v;
    for(int i=0;i<n;i++){
        v.push_back({endd[i]-start[i], i});
    }
    sort(v.begin(), v.end());
    int cou=0;
    for(int i=0;i<n;i++){
        int k=v[i].second;
            //cout<<start[k]<<" "<<endd[k]<<" "<<vis[start[k]]<<" "<<vis[endd[k]]<<endl;
        if(!vis[start[k]] && !vis[endd[k]]){
            vis[start[k]]=1;
            vis[endd[k]]=1;
            cou++;
            //cout<<start[k]<<" "<<endd[k]<<endl;
        }
        //cout<<v[i].first<<" "<<v[i].second<<endl;
    }
    cout<<cou<<endl;
}
