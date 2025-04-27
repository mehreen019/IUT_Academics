#include<iostream>
#include<stack>
using namespace std;
int main(void){
    stack<string> s;
    string x;
    int linecou=1,n;
    cin>>n;
    while(1){
        cin>>x;
        if(x=="-1")break;
        else if(x[0]=='<'){
            if(x[1]!='/') s.push(x);
            else {
                int j=2;
                while(x[j]!='\0'){
                    if(x[j]!=s.top()[j-1]){
                        cout<<"Error at line "<<linecou<<endl;
                        return 0;
                    }
                    //cout<<x[j];
                    j++;
                }
                s.pop();
                //cout<<x<<endl;
            }
        }
        if(cin.peek()=='\n') linecou++;
    }
    cout<<"No error"<<endl;
}
