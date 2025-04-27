#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,k;
    cin>>n>>k;
    int r[n];
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    sort(r,r+n);
    int amount=0, cou=0;
    for(int i=0;i<n;i++){
        amount+=r[i];
        if(amount>k) break;
        else cou++;
    }
    cout<<cou<<endl;
}
