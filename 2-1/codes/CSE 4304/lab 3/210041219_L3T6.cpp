#include<iostream>
#include<stack>
using namespace std;
int main(void){
    int n;
    cin>>n;
    fflush(stdin);
    while(n--){
        string s;
        getline(cin,s);
        stack<char> st;
        bool l=1;
        char x;
        for(int i=0;s[i]!='\0';i++){
            x=s[i];
            if(x=='[' || x=='(' || x=='{'){
                st.push(x);
            }
            else if(x=='}' || x==']' || x==')'){
                if(st.size()==0){
                    l=0; break;
                }
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
                    l=0; break;
                }
            }
           // cout<<x;
        }
        //if(st.size()!=0) l=0;
        if(l==0 || st.size()>0) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}
