#include<iostream>
#include<queue>
using namespace std;
int main(void){
    int n,k,x,y;
    priority_queue<int, vector<int>, greater<int>> back_heap;
    priority_queue<int> front_heap;
    cin>>x;
    front_heap.push(x);
    cout<<"median: "<<x<<endl;
    while(1){
        cin>>x;
        if(x==-1) break;
        if(x>front_heap.top()){
            back_heap.push(x);
        }
        else front_heap.push(x);
        int f=front_heap.size();
        int b=back_heap.size();
        if((f-b)>1){
            back_heap.push(front_heap.top());
            front_heap.pop();
            f--; b++;
        }
        else if((b-f)>1){
            front_heap.push(back_heap.top());
            back_heap.pop();
            f++; b--;
        }
        if(f==b){
            cout<<"median: "<<(front_heap.top()+back_heap.top())/2.00<<endl;
        }
        else if(f>b){
            cout<<"median: "<<front_heap.top()<<endl;
        }
        else cout<<"median: "<<back_heap.top()<<endl;
    }
}

