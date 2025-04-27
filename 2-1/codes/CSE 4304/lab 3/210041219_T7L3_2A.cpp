#include<iostream>
#include<stack>

using namespace std;
int main(void){
    int tst;
    string s;
    cin>>tst;
    while(tst--){
        cin>>s;
        int i=0,x,y;
        stack<int> st;
        while(s[i]!='\0'){
            if(s[i]>=48 && s[i]<=57){
                st.push(s[i]-'0');
                //cout<<st.top();
            }
            else {
                y=st.top();
                st.pop();
                x=st.top();
                st.pop();
                if(s[i]=='+') st.push(x+y);
                else if(s[i]=='-') st.push(x-y);
                else if(s[i]=='*') st.push(x*y);
                else if(s[i]=='/') st.push(x/y);

                //cout<<st.top();
            }
            i++;
        }
        cout<<st.top()<<endl;

    }
}
