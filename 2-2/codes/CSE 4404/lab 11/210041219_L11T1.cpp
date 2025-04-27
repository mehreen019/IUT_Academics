#include<bits/stdc++.h>
using namespace std;
const int MAXX=2e5+7;
double r[MAXX];

double weakness(double x,int n){
    double poorness=0,cur=0;
    for(int i=0;i<n;i++){
        cur+=(r[i]-x);
        if(cur<0){
            cur=0;
        }
        else{
            poorness=max(poorness, cur);
        }
    }
    cur=0;
    for(int i=0;i<n;i++){
        cur+=(x-r[i]);
        if(cur<0){
            cur=0;
        }
        else{
            poorness=max(poorness, cur);
        }
    }
    return poorness;
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    long double lo=-10000,hi=10000;
    while(hi-lo>0.000000000001){
        double m1=lo+(hi-lo)/3;
        double m2=hi-(hi-lo)/3;

        double f1=weakness(m1,n);
        double f2=weakness(m2,n);
        if(f1<f2){
            hi=m2;
        }
        else lo=m1;
    }
    cout<<fixed<<setprecision(15)<<weakness(lo,n)<<endl;
}
