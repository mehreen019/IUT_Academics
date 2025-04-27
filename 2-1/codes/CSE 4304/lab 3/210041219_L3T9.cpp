#include<iostream>
#include<stack>
using namespace std;
int main(void){
    string s;
    cin>>s;
    stack<char> st,ans;
    for(int i=0;s[i]!='\0';i++){
        if(st.size()==0) st.push(s[i]);
        else if(s[i]==st.top()){
            st.pop();
        }
        else st.push(s[i]);
    }
    if(st.size()==0) cout<<"NULL"<<endl;
    else{
        while(st.size()!=0){
            ans.push(st.top());
            //cout<<st.top();
            st.pop();
        }
        while(ans.size()!=0){
            cout<<ans.top();
            ans.pop();
        }
    }
}
