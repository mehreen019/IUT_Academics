#include<iostream>
#include<stack>
using namespace std;
int main(void){
    int n,q,x;
    cin>>n>>q;
    stack<int> st,m,h;
    for(int i=0;i<n;i++){
        cin>>x;
        st.push(x);
    }
    while(st.size()){
        m.push(st.top());
        st.pop();
    }

    while(q--){
        cin>>x;
        int in=1;
        while(x!=m.top()){
            //cout<<m.top();
            h.push(m.top());
            m.pop();
            in++;

        }
        cout<<in<<" ";
        int a=m.top();
        m.pop();
        while(!h.empty()){
            m.push(h.top());
            h.pop();
        }
        m.push(a);
    }
    cout<<endl;
}
//4 1 2 3 1 3 1
