#include<bits/stdc++.h>
using namespace std;
const int MAXX=206;

int dp[MAXX][100009], val[MAXX];

int solve(int n, int s1){
    if(s1==0) return 1;
    if(dp[n][s1]!=-1){ return dp[n][s1]; }
    else if(n==0){
        //if(s1==s2) return 1;
        return 0;
    }

    int p1=false, p2=false;
    if(s1-val[n]>=0) p1=solve(n-1, s1- val[n]);
    p2=solve(n-1, s1);
    cout<<n<<" "<<p1<<" "<<p2<<" "<<s1<<endl;

    return dp[n][s1]= (p1 | p2);
}

int main(void){
    int n, sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        sum+=val[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=sum/2;j++){
            dp[i][j]=-1;
        }
    }
    if(sum%2) cout<<"false"<<endl;
    else{
        solve(n, sum/2);
        if(dp[n][sum/2]==0) cout<<"false"<<endl;
        else cout<<"true"<<endl;
    }
}
