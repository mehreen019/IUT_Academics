#include<iostream>
#include<deque>
using namespace std;
int main(void){
    int tst;
    cin>>tst;
    while(tst--){
        string s;
        deque<char> d;
        deque<char> b;
        cin>>s;
        bool l=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='['){
                l=1;
            }
            else if(s[i]==']'){
                l=0;
            }
            else{
            if(l){
                if(s[i-1]=='[') b.push_front(s[i]);
                else b.push_back(s[i]);
            }
            else{
                d.push_back(s[i]);
            }
            }
        }
        while(!b.empty()){
            cout<<b.front();
            b.pop_front();
        }

        while(!d.empty()){
            cout<<d.front();
            d.pop_front();
        }
    }
}
