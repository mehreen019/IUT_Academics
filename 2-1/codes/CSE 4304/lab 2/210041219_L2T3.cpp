#include<iostream>
using namespace std;
int main(void){
    int n;
    string s;
    cin>>n>>s;
    for(int i=0;i<n;i++){
        if(s[i]=='d' && s[i+1]=='u' && s[i+2]=='b'){
            cout<<" ";
            i=i+2;
        }
        else cout<<s[i];
    }
}
