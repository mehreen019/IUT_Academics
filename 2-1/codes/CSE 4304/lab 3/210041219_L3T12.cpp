#include<iostream>
#include<stack>
using namespace std;
int main(void){
    string s;
    int tst,n;
    cin>>tst;
    while(tst--){
        cin>>n>>s;
        stack<char> st;
        for(int i=0;i<n;i++){
           if(st.size()==0) st.push(s[i]);
           else if(s[i]==')') {
                if(st.top()=='(') st.pop();
                else st.push(s[i]);
           }
           else st.push(s[i]);
        }
        cout<<st.size()/2<<endl;
    }
}
