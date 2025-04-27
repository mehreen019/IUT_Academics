#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int main(void){
    while(1){
    queue<int> q;
    int n;
    cin>>n;
    if(n==0) break;
    else{
        vector<int> v;
        for(int i=1;i<=n;i++){
            q.push(i);
        }
        while(q.size()>1){
            v.push_back(q.front());
            q.pop();
            q.push(q.front());
            q.pop();
        }
        cout<<"DISCARDED CARDS: ";
        for(int i=0;i<v.size();i++){
            cout<<v[i]<<" ";
        }
        cout<<endl<<"REMAINING CARDS: "<<q.front()<<endl;
        q.pop();
    }
    }
}
