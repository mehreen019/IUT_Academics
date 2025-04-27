#include<iostream>
using namespace std;
int main(void){
    int n,x,rr=0,size=0,fr=0,maxs=5;
    int q[maxs]={0};
    while(1){
        cin>>x;
        if(x==-1) break;
        else if(x==1){
            int num;
            cin>>num;
            if(size==maxs) cout<<"Push_front: Overflow"<<endl;
            else{
                q[fr]=num;
                size++;
                if(rr<=fr) rr=(fr+size)%maxs;
                fr--;
                if(fr<0) fr=maxs-1;
                //cout<<fr;
                cout<<"Push_front: ";
                for(int i=1;i<=size;i++){
                    cout<<q[(fr+i)%maxs]<<" ";
                }
                cout<<endl;
               // cout<<"front"<<fr<<"rear:"<<rr<<endl;
            }
        }
        else if(x==2){
            int num;
            cin>>num;
            if(size==maxs) cout<<"Push_back: Overflow"<<endl;
            else{
                q[rr]=num;
                rr=(rr+1)%maxs;
                size++;
                cout<<"Push_back: ";
                for(int i=1;i<=size;i++){
                    cout<<q[(fr+i)%maxs]<<" ";
                }
                cout<<endl;
                //cout<<"front"<<fr<<"rear:"<<rr<<endl;
            }
        }
        else if(x==3){
            if(size==0) cout<<"Pop_front: Underflow";
            else{
                fr=(fr+1)%n;
                size--;
                cout<<"Pop_front: ";
                for(int i=1;i<=size;i++){
                    cout<<q[(fr+i)%maxs]<<" ";
                }
                cout<<endl;
            }
        }
        else if(x==4){
           if(size==0) cout<<"Pop_back: Underflow";
            else{
                rr--;
                if(rr<0) rr=maxs-1;
                size--;
                cout<<"Pop_back: ";
                for(int i=1;i<=size;i++){
                    cout<<q[(fr+i)%maxs]<<" ";
                }
                cout<<endl;
            }
        }
        else if(x==5){
            cout<<"Size: "<<size<<endl;
        }
        else if(x==6){
            break;
        }
    }

}
//1 push_front
//2 push_back
//3 pop_front
//4 pop_back
//5 size
//6 exit
