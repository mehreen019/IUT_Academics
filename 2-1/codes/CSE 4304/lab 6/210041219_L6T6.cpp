#include<iostream>
#include<map>
#include<queue>
using namespace std;
int main(void){
    string s;
    map<char, int> m;
    cin>>s;
    int n=s.size();
    for(int i=0;i<n;i++){
        m[s[i]]++;
    }
    priority_queue<pair<int,char>> pq;
    for(auto it:m){
        pq.push(make_pair(it.second, it.first));
    }
    while(!pq.empty()){
        pair<int, char> p=pq.top();
        while(p.first--){
            cout<<p.second;
        }
        pq.pop();
    }
    cout<<endl;
}
