#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,x,y,idx=1,type;
    cin>>n;
    map<int,vector<int>> m;
    while(n--){
        cin>>type>>x;
        if(type==1){
                //cout<<"ok";
            m[x].push_back(idx);
            idx++;
            /*for(int i=0;i<m[x].size();i++){
            cout<<m[x][i]<<" ";
            }*/
        }
        else{
            cin>>y;
            if(x!=y){
                for(int i=0;i<m[x].size();i++){
                m[y].push_back(m[x][i]);
                }
                m[x].clear();
            }
            //cout<<m[y][0]<<"ok";

        }
        //cout<<endl;
    }
    vector<int> v(idx,0);
    //cout<<"ok";
        for(auto it:m){
            //cout<<it.first<<": ";
            for(int i=0;i<m[it.first].size();i++){
                v[it.second[i]]=it.first;
                //cout<<it.second[i]<<" ";
            }
            //cout<<endl;
        }
        for(int i=1;i<v.size();i++){
            cout<<v[i]<<" ";
        }
}
