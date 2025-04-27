#include<iostream>
using namespace std;
int main(void){
    string s,in;
    cin>>in>>s;
    s+=s;
    int j=0,cou=0;
    for(int i=0;i<s.size();i++){
        while(s[i]==in[j]){
            cou++;
            j++;
            i++;
        }
        if(cou==in.size()){ cout<<"YES"<<endl; return 0;}
        else { cou=0; j=0; }
    }
    cout<<"NO"<<endl;
}
