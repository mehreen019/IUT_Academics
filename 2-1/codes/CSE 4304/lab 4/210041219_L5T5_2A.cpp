#include<iostream>
#include<queue>
using namespace std;
int main(void){
    int idx=0,n=0,x,cou=0;
    queue<int> q;
    while(1){
        cin>>x;
        if(x==-1) break;
        else{
            q.push(x);
            n++;
        }
    }
    cin>>x;
    while(1){
        q.front()--;
        cou++;
        if(q.front()==0){
            if(idx==x) break;
            else if(idx<x) { idx--; x--; n--;}
            else {n--; idx--;}
        }
        else q.push(q.front());
        q.pop();
        idx=(idx+1)%n;
        }
    cout<<cou<<endl;
}
