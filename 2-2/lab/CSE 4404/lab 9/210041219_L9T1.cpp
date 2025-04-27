#include<bits/stdc++.h>
using namespace std;
const int MAXX=1e4+9;

int dp[15][MAXX], val[15];

int solve(int k,int n){
    if(dp[n][k]!=-1){ return dp[n][k]; }
    else if(n==0) return INT_MAX;
    else if(k<=0) return 0;

    int p=INT_MAX, p1, p2;
    if(k-val[n]>=0){ p1=solve(k-val[n], n); if(p1!=INT_MAX) p=min(p, p1+1); }
    p2=solve(k, n-1);  p=min(p, p2);
    //cout<<n<<" "<<p<<" "<<k<<endl;
    //if(p==INT_MAX || p==INT_MIN) p=INT_MAX;

    return dp[n][k]=p;
}

int main(void){
    int n, amount;
    cin>>n>>amount;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=amount;j++){
            dp[i][j]=-1;
        }
    }
    if(amount==0) cout<<0<<endl;
    else{
    solve(amount, n);
    if(dp[n][amount]==INT_MAX) cout<<-1<<endl;
    else cout<<dp[n][amount]<<endl;
    }
}
