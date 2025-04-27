#include<bits/stdc++.h>
using namespace std;
int main(void){
    stack<char> st,help;
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]!='<'){
            st.push(s[i]);
        }
        else st.pop();
    }
    while(!st.empty()){
        help.push(st.top());
        st.pop();
    }
    while(!help.empty()){
        cout<<help.top();
        help.pop();
    }
}
