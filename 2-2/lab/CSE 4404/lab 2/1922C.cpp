#include<bits/stdc++.h>
using namespace std;
int main(void){
    int tst,n,q,x,y;
    cin>>tst;
    while(tst--){
        cin>>n;
        int r[n];
        for(int i=0;i<n;i++){
            cin>>r[i];
        }
        int fc[n], bk[n], cou=0;
        fc[0]=0, bk[n-1]=0;
        for(int i=0;i<n-1;i++){
            if(r[i+1]-r[i]> r[i]-r[i-1] && i!=0) cou+=r[i+1]-r[i];
                else{ cou+=1; }
            fc[i+1]=cou;
        }
        cou=0;
        for(int i=n-1;i>0;i--){
            if(r[i+1]-r[i]< r[i]-r[i-1] && i!=(n-1)) cou+=r[i]-r[i-1];
                    else{ cou+=1; }
            bk[i-1]=cou;
        }
        /*for(int i=0;i<n;i++){
            cout<<fc[i]<<" "<<bk[i]<<endl;
        }*/
        cin>>q;
        while(q--){
            int cou=0;
            cin>>x>>y;
            if(x<y){
                cout<<min(fc[y-1]-fc[x-1], r[y-1]-r[x-1])<<endl;
            }
            else{
                for(int i=x-1;i>=y;i--){
                    if(r[i+1]-r[i]< r[i]-r[i-1] && i!=(n-1)) cou+=r[i]-r[i-1];
                    else{ cou+=1; }
                }
                cout<<min(bk[y-1]-bk[x-1], r[x-1]-r[y-1])<<endl;
            }
        }
    }
}
