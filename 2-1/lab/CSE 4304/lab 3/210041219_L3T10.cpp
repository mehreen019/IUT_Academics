#include<iostream>
#include<stack>
using namespace std;
int main(void){
    int n;
    stack<int> m,h;
    cin>>n;
    int r[n];
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    int i=0;
    while(i<n){
        if(r[i]==1){ m.push(r[i]);}
        else{
            h.push(r[i]);
        }
        while(!m.empty() && !h.empty() && m.top()+1==h.top()){
            m.push(h.top());
            h.pop();
        }
        i++;

    }
    if(m.size()==n) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}
