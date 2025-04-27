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
    ll h=0; //pattern to match's hash value
    ll rh=0; //string's hash value

    ll p=1, tp;
    for(int i=0;i<m-1;i++){
        p=(p*b)%MOD; //init power value to highest. MOD to prevent overflow
    }

    ll cou=0; tp=1;
    for(int i=m-1;i>=0;i--){
        h+=(((pat[i])*tp) % MOD);//pattern hash
        h=h%MOD;
        rh+=(((st[i])*tp) % MOD);//first window hash
        rh=rh%MOD;
        tp=(tp*b)%MOD;
    }

    if(rh==h){
        int t=0; cou++;
            for( ;t<m;t++){
                if(st[t]!=pat[t]){ cou--; break;} //if words don't match despite hash value being same, break
        }
    }

    for(int i=1;i<=n-m;i++){

        ///calculate successive window's hash
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
    }
    return cou;
}

int main(void){
    string st,pat;
    cin>>st>>pat;
    cout<<rabin_karp(st,pat)<<endl;
}
