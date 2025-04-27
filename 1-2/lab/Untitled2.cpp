#include<bits/stdc++.h>
using namespace std;
int main(void){
    long long n,n1,m,ans=1;
    double t=0;
    cin>>n;
    n1=n;
    long long ar[n];

    for(int i=0;i<n;i++){ cin>>ar[i];
            if(ar[i] == 0){
            cout<<0<<endl;
            return 0;
        }
    }
    int i=0;
    while(n1--){
        m=ar[i];
        if(ans>1000000000000000000){
            cout<<-1<<endl;
            return 0;
        }
        ans=(ans*m);
        t+=log10(m);
        i++;
    }
    //cout<<t<<" ";
    if(t>18.1){
        cout<<-1<<endl;
        return 0;
    }
    if(ans>1000000000000000000)cout<<-1<<endl;
    else cout<<ans<<endl;
}
