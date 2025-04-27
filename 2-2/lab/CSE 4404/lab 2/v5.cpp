#include<bits/stdc++.h>
using namespace std;
int main(void){
    int tst,n;
    cin>>tst;
    while(tst--){
        cin>>n;
        int r[n], m=INT_MIN, idx;
        for(int i=0;i<n;i++){
            cin>>r[i];
            m=max(m,r[i]);
            if(m==r[i]) idx=i;
        }
        int cost=0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(r[j]<r[i]){
                    //cost+= j-i;
                    int k=j, t=r[j];
                    while(k!=i){
                        r[k]=r[k-1];
                        cost++;
                        k--;
                    }
                    r[i]=t;
                }
            }
        }
        cout<<"Optimal train swapping takes "<<cost<<" swaps."<<endl;
    }
}
