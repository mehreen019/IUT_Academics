#include<bits/stdc++.h>
using namespace std;
int main(void){
    int tst,n;
    cin>>tst;
    while(tst--){
        cin>>n;
        int r[n];
        map<int, vector<int>> m;
        for(int i=0;i<n;i++){
            cin>>r[i];
            m[r[i]].push_back(i);
        }
        bool ans=0;
        for(auto it:m){
            //if(it.second.size()>1){
                sort(it.second.begin(), it.second.end());
                for(int i=0;i<it.second.size();i++){
                    for(int j=i+1; j<it.second.size();j++){
                        if(it.second[j]-it.second[i]>1){
                            ans=1; break;
                        }
                    }
                    if(ans) break;
                }
                //cout<<it.second[0]<<" "<<it.second[1]<<endl;

            //}
            if(ans) break;
        }
        if(ans) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
