#include<bits/stdc++.h>
using namespace std;
int main(void){
    map<int, int>m;
    int target,x,cou=0;
    while(1){
        cin>>x;
        if(x==-1) break;
        else{
            m[x]++;
        }
    }
    cin>>target;
    for(auto i:m){
        int k=target-i.first;
        if(m[k]>0){
        while(m[k]>0 && m[i.first]>0){
            cout<<"( "<<i.first<<", "<<k<<") ";
            m[i.first]--;
            m[k]--;
            cou++;
        }
        }else{
            m.erase(k);
        }
    }
    if(cou==0) cout<<"No pairs found"<<endl;
}
