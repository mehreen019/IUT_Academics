#include<iostream>
#include<stack>
using namespace std;
int main(void){
    int n,j=0,i=1,len=0;;
    string s;
    getline(cin, s);
    cin>>n;
    while(1){
        if(i==s[j]-'0'){
            cout<<"Push"<<endl;
            j+=2;
        }
        else{
            cout<<"Push Pop"<<endl;
        }
        i++;
        if(i==n+1 || (s[j-1]=='\0' && j!=0)) break;
    }
}
