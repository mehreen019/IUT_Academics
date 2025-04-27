#include<bits/stdc++.h>
using namespace std;
int main(void){
    int tst;
    cin>>tst;
    int origin=tst;
    while(tst--){
        stack<char> fr,bk,help;
        string s;
        if(tst==origin-1)cin.ignore();
        getline(cin,s);
        //cout<<s<<endl;
        int state=0,fpush=0;
        for(int i=0;i<s.size();i++){
            if(s[i]==']'){  state=0;}
            else if(s[i]=='[') {state=1; fpush=1;}
            else if(s[i]=='<'){
                if(state){
                    if(!fpush){
                        if(!fr.empty())fr.pop();
                    }
                }
                else {
                    if(!bk.empty())bk.pop();
                }
            }
            else{
                if(state==0){
                    bk.push(s[i]);
                }
                else if(state==1){
                    if(fpush){
                        while(!fr.empty()){
                            help.push(fr.top());
                            fr.pop();
                        }
                        fr.push(s[i]);
                        fpush=0;
                    }
                    else fr.push(s[i]);
                }
            }
            //cout<<s[i];
        }
        while(!fr.empty()){
            help.push(fr.top());
            fr.pop();
        }
        while(!help.empty()){
            cout<<help.top();
            help.pop();
        }
        while(!bk.empty()){
            help.push(bk.top());
            bk.pop();
        }
        while(!help.empty()){
            cout<<help.top();
            help.pop();
        }
        cout<<endl;
    }
}
