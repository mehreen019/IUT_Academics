#include<iostream>
#include<queue>
using namespace std;
int main(void){
    int n,k,x,cou=0,ans=0,y;
    priority_queue<int> pq;
    while(1){
        cin>>x;
        if(x==-1) break;
        else pq.push(x);
    }
    while(pq.size()>1){
        x=pq.top(); pq.pop();
        y=pq.top(); pq.pop();
        int t=x-y;
        if(t>0) pq.push(t);
    }
    if(!pq.empty()) cout<<pq.top()<<endl;
    else cout<<0<<endl;
}
