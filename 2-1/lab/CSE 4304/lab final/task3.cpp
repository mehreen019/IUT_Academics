//2 4 5 6 7 8 10 15
//1 3 9 11 13 14 16
#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n;
    cin>>n;
    int ab[n],cou=0;
    int nosh[n];
    for(int i=0;i<n;i++){
        cin>>ab[i];
    }
    for(int i=0;i<n;i++){
        cin>>nosh[i];
    }
    sort(nosh,nosh+n);
    sort(ab,ab+n);
    int k=0,p=0;
    while(k<n){
        if(ab[k]>nosh[p]){
            cou++; p++;
        }
        k++;
    }
    cout<<cou<<endl;
}
