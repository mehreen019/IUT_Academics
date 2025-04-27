#include<bits/stdc++.h>
using namespace std;
int main(void){
    string s;
    int n;
    cin>>s>>n;
    sort(s.begin(),s.end());
    int i=1;
    while(i!=n){
        next_permutation(s.begin(),s.end());
        cout<<s<<" ";
        i++;
    }
    cout<<s<<endl;
}
