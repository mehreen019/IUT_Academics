#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int b=350;
const ll MOD=1e9 + 10;

ll rabin_karp(string st, string pat){
    ll n= st.size();
    ll m= pat.size();
    if(n<m) return 0;
    if(n==0 || m==0) return 0;
    ll h=0; //for pat
    ll rh=0; //for string
    ll p=1, tp;
    for(int i=0;i<m-1;i++){
        p=(p*b)%MOD; //power value
    }
    ll cou=0; tp=1;
    for(int i=m-1;i>=0;i--){
        h+=(((pat[i])*tp) % MOD);//pat hash
        h=h%MOD;
        rh+=(((st[i])*tp) % MOD);//first window hash
        rh=rh%MOD;
        tp=(tp*b)%MOD;
    }
    if(rh==h){
        int t=0; cou++;
            for( ;t<m;t++){
                if(st[t]!=pat[t]){ cou--; break;
            }
    }}

    //cout<<p<<"  "<<h<<"      "<<rh<<endl;
    for(int i=1;i<=n-m;i++){
        rh=(rh - (((st[i-1])*p)%MOD) )%MOD ;
        rh=(rh+MOD)%MOD;
        rh=(rh*b)%MOD;
        rh=(rh+ st[i+m-1])%MOD;
        if(rh==h){
            int t=i,j=0; cou++;}/*
            for( ;t<i+m;t++){
                if(st[t]!=pat[j]){ cou--; break;}
                j++;
            }
        }*/
        //cout<<rh<<"     ";
    }
    return cou;
}

int main(void){
    string st,pat;
    cin>>st>>pat;
    cout<<rabin_karp(st,pat)<<endl;
}
