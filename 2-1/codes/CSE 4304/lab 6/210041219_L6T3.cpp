#include<iostream>
#include<queue>
using namespace std;
int main(void){
    int n,k,x,cou=0,ans=0,y;
    cin>>n>>k;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0;i<n;i++){
        cin>>x;
        if(x<k) cou++;
        pq.push(x);
    }
    while(cou>0){
        x=pq.top(); pq.pop(); cou--;
        y=pq.top(); pq.pop(); cou--;
        int t=x+y*2;
        if(t<k) cou++;
        pq.push(t);
        ans++;
    }
    cout<<ans<<endl;
}
