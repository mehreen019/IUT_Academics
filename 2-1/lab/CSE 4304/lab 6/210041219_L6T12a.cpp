#include<iostream>
#include<queue>
using namespace std;
int main(void){
    while(1){
    int n,x,y;
    cin>>n;
    if(n==0) break;
    priority_queue<int,vector<int>,greater<int>> p;
    int ans=0,res=0;
    for(int i=0;i<n;i++){
            cin>>x;
            p.push(x);
    }
    while(p.size()>1){
        x=p.top();
        p.pop();
        y=p.top();
        p.pop();
        ans=x+y;
        p.push(ans);
        res+=ans;
    }
    cout<<res<<endl;
    }
}
