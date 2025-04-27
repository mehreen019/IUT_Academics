#include<bits/stdc++.h>
using namespace std;
int main(void){
    map<string, int>m;
    string s,sm,t="";
    while(1){
        getline(cin,s);
        if(s.size()==0) break;
        else sm=s;
    }
    for(int i=0;i<sm.size();i++){
        if((sm[i]>=32 && sm[i]<=47) || sm[i]=='`'){
            m[t]++;
            t="";
        }
        else{
            t=t+sm[i];
        }
    }
    m[t]++;
    for(auto i:m){
        if(i.second>1 && i.first!=""){
            cout<<i.first<<" "<<i.second<<endl;
        }
    }
}
