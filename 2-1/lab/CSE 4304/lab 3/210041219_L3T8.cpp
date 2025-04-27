#include<iostream>
#include<stack>
using namespace std;
int main(void){
    stack<char> st;
    char x;
    int linecou=1,n;
    cin>>n;
    while(1){
        cin>>x;
        if(x=='[' || x=='(' || x=='{'){
                st.push(x);
            }
            else if(x=='}' || x==']' || x==')'){
                if(x=='}' && st.top()=='{'){
                    st.pop();
                }
                else if(x==')' && st.top()=='('){
                    st.pop();
                }
                else if(x==']' && st.top()=='['){
                    st.pop();
                }
                else{
                    cout<<"ERROR"<<endl;
                    return 0;
                }
            }
        if(cin.peek()=='\n') linecou++;
        if(linecou>=n) break;
    }
    cout<<"No error"<<endl;
}
