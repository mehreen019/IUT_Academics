#include<iostream>
#include<map>
#include<queue>
using namespace std;
int main(void){
    int n,num;
    map<int, int> m;
    while(1){
        cin>>n;
        if(n==-1) break;
        else{
            m[n]++;
        }
    }
    cin>>num;
    priority_queue<pair<int,int>> pq;
    for(auto it:m){
        pq.push(make_pair(it.second, it.first));
    }
    while(num--){
        pair<int, int> p=pq.top();
        cout<<p.second<<" ";
        pq.pop();
    }
}
