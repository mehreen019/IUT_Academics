#include<bits/stdc++.h>
using namespace std;
int main(void){
    string rev;
    while(cin>>rev){
        string  s=rev;
        reverse(rev.begin(),rev.end());
        int cou=0,n=s.size(),idx=0;
        for(int i=0;i<n;i++){
            if(rev[0]==s[i]){
                idx=i;
                int j=0;
                for( ;j<n;j++){
                    if(s[idx]==rev[j]){
                        cou++; idx++;
                        if(idx==n){ j++; break;}
                    }
                    else break;
                }
                if(cou==n-i){ idx=j; break;}
                else idx=-1;
            }
        }
        if(idx==-1 || idx==n){
            cout<<s<<endl;
        }
        else{
            cout<<s;
            for(int i=idx;i<n;i++){
                cout<<rev[i];
            }
            cout<<endl;
        }
    }
}
//lashlarlana
//analralhsal
