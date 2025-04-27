//amanaplanacanal
//lanacanalpanama
//xyz
//zyx
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int b=350;
const ll MOD=1e9 + 10;

void rehash(string s, string rev){
    ll n=s.size();
    ll fr[n], bk[n],hash_val=b;
    fr[n-1]=s[n-1];
    bk[0]=rev[0];
    for(ll i=1;i<n;i++){
        fr[n-i-1]=( (s[n-i-1]%MOD) * (hash_val%MOD) )%MOD;
        fr[n-i-1]= ((fr[n-i-1]%MOD) + (fr[n-i]%MOD))%MOD;
        hash_val= ((hash_val%MOD) * (b%MOD))%MOD;

        bk[i]=rev[i];
        bk[i]=((bk[i]%MOD) + ((bk[i-1]%MOD)*(b%MOD))%MOD)%MOD;
    }
    /*for(int i=0;i<n;i++){
        cout<<bk[i]<<" "<<fr[n-i-1]<<endl;
    }*/
    int cou;
    for(int idx=0;idx<n;idx++){
        if(bk[idx]==fr[n-idx-1]){ cou=idx; }
    }
    cout<<s;
    for(int i=cou+1;i<n;i++){
        cout<<rev[i];
    }
    cout<<endl;
}

int main(void){
    string rev;
    while(cin>>rev){
        string  s=rev;
        reverse(rev.begin(),rev.end());
        rehash(s, rev);
    }
}
//lashlarlana
//analralhsal
