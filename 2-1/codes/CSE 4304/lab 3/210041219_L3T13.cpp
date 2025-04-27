#include<iostream>
#include<stack>
using namespace std;
int main(void){
    string s;
    cin>>s;
    stack<char> st;
    int cou=0;
    for(int i=0;s[i]!='\0';i++){
        if(st.size()==0) st.push(s[i]);
        else if(s[i]==')') {
            if(st.top()=='('){ st.pop(); cou+=2;}
            else st.push(s[i]);
        }
        else st.push(s[i]);
    }
    cout<<cou;
}
