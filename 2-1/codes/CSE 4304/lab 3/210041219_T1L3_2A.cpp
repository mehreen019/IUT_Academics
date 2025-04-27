#include<iostream>
using namespace std;
int main(void){
    int n,i=-1,x,r[100000];
    cin>>n;
    while(1){
        cin>>x;
        if(x==-1) break;
        else{
            if(x==1){
                int to_push;
                cin>>to_push;
                if(i==n-1) cout<<"Overflow"<<endl;
                else {i++;
                r[i]=to_push;
                for(int j=0;j<=i;j++){
                    cout<<r[j]<<" ";
                }
                cout<<endl;
                }
            }
            else if(x==2){
                if(i==-1) cout<<"Underflow"<<endl;
                else{ i--;
                for(int j=0;j<=i;j++){
                    cout<<r[j]<<" ";
                }
                cout<<endl;
                }
            }
            else if(x==3){
                if(i==-1) cout<<"True"<<endl;
                else cout<<"False"<<endl;
            }
            else if(x==4){
                if(i==n-1) cout<<"True"<<endl;
                else cout<<"False"<<endl;
            }
            else if(x==5){
                cout<<i+1<<endl;
            }
            else if(x==6){
                cout<<r[i]<<endl;
            }
        }
    }

}
//1==push
//2==pop
//3==isEmpty
//4==isFull
//5==size
//6==top
