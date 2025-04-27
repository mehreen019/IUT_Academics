#include<iostream>
#include<stack>
using namespace std;
int main(void){
    int i=0,x;
    stack<int> s,ans,temp;
    while(1){
        cin>>x;
        if(x==-1) break;
        else{
            s.push(x);
            i++;
        }
    }
    temp.push(s.top());
    s.pop();
    ans.push(-1);
    while(!s.empty()){
        while(s.top()>=temp.top()) {
           //cout<<temp.top();
           temp.pop();
           if(temp.empty()) break;
        }
        //cout<<s.top();
        if(temp.size()==0){
            //cout<<s.top()<<" ";
            temp.push(s.top());
            ans.push(-1);
            s.pop();
        }
        else{
            ans.push(temp.top());
            temp.push(s.top());
            s.pop();
            //cout<<ans.top()<<" ";
        }


    }
    while(ans.size()){
        cout<<ans.top()<<" ";
        ans.pop();
    }
}
