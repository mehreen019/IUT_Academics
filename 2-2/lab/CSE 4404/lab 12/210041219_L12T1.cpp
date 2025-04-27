#include<bits/stdc++.h>
using namespace std;
//map<char, int> smol,big;
vector<pair<int,int> > indices;

string getNice(string s){
    int n=s.size(),start=0,endd=0;
    string neww="";
    map<char,int> mp,topr;
    for(int i=0;i<n;i++){
        if(s[i]>='a' && s[i]<='z'){
            char up=toupper(s[i]);
            if(s.find(up)==string::npos){
                if(topr.size()==0 && start!=i){
                    indices.push_back({start,i});
                }
                topr.clear();
                mp.clear();
                start=i+1;
                continue;
            }
                if(mp[up]==0){
                    mp[s[i]]++;
                    topr[s[i]]++;
                }
                else{
                    topr[s[i]]=0;
                    topr[up]=0;
                    mp[s[i]]++;
                    endd=i;
                }
            }
            else{
                char low=tolower(s[i]);
                if(s.find(low)==string::npos){
                    if(topr.size()==0){
                        indices.push_back({start,i});
                    }
                    topr.clear();
                    start=i+1;
                    continue;
                }
                if(mp[low]==0){
                    mp[s[i]]++;
                    topr[s[i]]++;
                }
                else{
                    topr[s[i]]=0;
                    topr[low]=0;
                    mp[s[i]]++;
                    endd=i;
                }
            }

        }
    if(topr.size()){
        indices.push_back({start,endd});
    }
    pair<int,int> maxdist;
    maxdist.first=-1;
    maxdist.second=-1;
    for(int i=0;i<indices.size();i++){
        cout<<indices[i].first<<" "<<indices[i].second<<endl;
        if(maxdist.first==-1 && maxdist.second==-1){
            maxdist.first=indices[i].first;
            maxdist.second=indices[i].second;

        }
        else{
            if(maxdist.second-maxdist.first < indices[i].second-indices[i].first){
                maxdist.first=indices[i].first;
                maxdist.second=indices[i].second;
            }
        }
    }
    if(maxdist.first!=-1 && maxdist.second!=-1){
        for(int i=maxdist.first;i<=maxdist.second;i++){
            neww+=s[i];
            //cout<<neww<<" "<<s[i]<<endl;
        }
    }
    return neww;
}

int main(void){
    int n;
    string s;
    cin>>s;
    n=s.size();
    cout<<getNice(s)<<endl;
}
//bCcDyCBbD
