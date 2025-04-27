#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXX=20005;
const int MOD=1e9+7;
ll dp[MAXX];

int main(void){
    int n;
    ll ans=0;
    cin>>n;
    dp[1]=1;
    dp[2]=2;
    for(int i=3;i<=n;i++){
        dp[i]= ((  ((dp[i-1])%MOD) + ((dp[i-2]%MOD)*(i-1))%MOD )%MOD ) ;
    }
    cout<<dp[n];
}
