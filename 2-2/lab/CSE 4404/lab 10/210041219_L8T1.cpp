#include<bits/stdc++.h>
using namespace std;
const int MAXX=2e5+7;
int r[MAXX],n;

int calcSum(int l, int h, int m){
    int leftSum=INT_MIN, rightSum=INT_MIN, tl=0,tr=0;
    for(int i=m;i>=0;i--){
        tl+=r[i];
        leftSum=max(tl,leftSum);
    }
    for(int i=m+1;i<n;i++){
        tr+=r[i];
        rightSum=max(tr,rightSum);
    }

    //cout<<l<<" "<<h<<" "<<leftSum<<" "<<rightSum<<endl;
    return max(max(leftSum, rightSum), leftSum+rightSum);
}

int sum(int l,int h){
    if(l==h) return r[l];
    else if(l>h) return INT_MIN;

    int m=(l+h)/2;
    if(m==l || m==h) return max(max(r[l], r[h]), r[l]+r[h]);
    //cout<<l<<" "<<h<<endl;
    return max(calcSum(l,h,m), max(sum(l, m), sum(m+1,h) ) );
}

int main(void){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    int l=0, h=n-1,m, maxsum=0;
    maxsum=sum(l,h);
    cout<<maxsum<<endl;
}
