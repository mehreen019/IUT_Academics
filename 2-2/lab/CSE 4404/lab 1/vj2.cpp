#include<bits/stdc++.h>
using namespace std;
int main(void){
    int tst, len, n, ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){
        cin.ignore();
        cin>>len>>n;
        string t;
        vector<string> st;
        map<int, vector<string>> m;
        for(int i=0;i<n;i++){
            cin>>t;
            st.push_back(t);
        }
        for(int k=0;k<n;k++){
            int cou=0;
            for(int i=0;i<len;i++){
                for(int j=i+1;j<len;j++){
                    if(st[k][i] > st[k][j]){
                        cou++;
                    }
                }
            }
            m[cou].push_back(st[k]);
        }
        for(auto it:m){
            for(int i=0;i<it.second.size();i++){
                cout<<it.second[i]<<endl;
            }
        }
        if(tst>0) cout<<endl;
    }
}
