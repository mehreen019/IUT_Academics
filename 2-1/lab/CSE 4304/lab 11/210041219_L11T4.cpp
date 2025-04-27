#include<bits/stdc++.h>
using namespace std;
int main(void){
    string s,t="";
    map<string, string> m;
    vector<string> v;
    while(1){
        getline(cin,s);
        if(s.size()==0) break;
        else{
            for(int i=0;i<s.size();i++){
            if(s[i]==' ' ){
                v.push_back(t);
                //cout<<t<<" ";
                t="";
            }
            else{
            t=t+s[i];}}
            v.push_back(t);
            t="";
    }}
    for(int i=1;i<v.size();i+=2){
        m[v[i]]=v[i-1];
        //cout<<v[i]<<" ";
    }
    while(1){
        cin>>s;
        if(s=="-1") break;
        if(m[s]!="") cout<<m[s]<<endl;
        else cout<<"eh"<<endl;
    }
    /*for(auto i:m){
        cout<<i.first<<" "<<i.second<<endl;
    }*/
}
