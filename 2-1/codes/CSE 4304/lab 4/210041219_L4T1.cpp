#include<iostream>
using namespace std;
int main(void){
    int n,x,rr=0,size=0,fr=0;
    cin>>n;
    int q[n]={0};
    while(1){
        cin>>x;
        if(x==-1) break;
        else if(x==1){
            int num;
            cin>>num;
            if(size==n) cout<<"Enqueue: Overflow"<<endl;
            else{
                q[rr]=num;
                rr=(rr+1)%n;
                size++;
                cout<<"Enqueue: ";
                for(int i=0;i<size;i++){
                    cout<<q[(fr+i)%n]<<" ";
                }
                cout<<endl;
            }
        }
        else if(x==2){
            if(size==0) cout<<"Dequeue: Underflow";
            else{
                fr=(fr+1)%n;
                size--;
                cout<<"Dequeue: ";
                for(int i=0;i<size;i++){
                    cout<<q[(fr+i)%n]<<" ";
                }
                cout<<endl;
            }
        }
        else if(x==3){
            if(size==0) cout<<"isEmpty: True"<<endl;
            else cout<<"isEmpty: False"<<endl;
        }
        else if(x==4){
            if(size==n) cout<<"isFull: True"<<endl;
            else cout<<"isFull: False"<<endl;
        }
        else if(x==5){
            cout<<"Size: "<<size<<endl;
        }
        else if(x==6){
            cout<<"Front: "<<q[fr]<<endl;
        }
    }

}
//1 enqueue
//2 dequeue
//3 isEmpty
//4 isFull
//5 size
//6 front
