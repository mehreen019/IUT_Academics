#include<iostream>
#include<stack>
using namespace std;
int main(void){
    int n,q,x,size=0;
    cin>>n>>q;
    stack<int> mainn,help;
    while(q--){
        cin>>x;
        if(x==1){
            int num;
            cin>>num;
            if(size==n) cout<<"Size: "<<size<<" Elements: Overflow"<<endl;
            else{
                mainn.push(num);
                size++;
                cout<<"Size: "<<size<<endl;
                cout<<"Elements: ";
                while(!mainn.empty()){
                    help.push(mainn.top());
                    mainn.pop();
                }
                while(!help.empty()){
                    cout<<help.top()<<" ";
                    mainn.push(help.top());
                    help.pop();
                }
                cout<<endl;
            }
        }
        else if(x==2){

            if(size==0) cout<<"Size: "<<size<<" Elements: NULL"<<endl;
            else{
                while(!mainn.empty()){
                    help.push(mainn.top());
                    mainn.pop();
                }
                help.pop();
                size--;
                if(size==0) cout<<"Size: "<<size<<" Elements: NULL"<<endl;
                else{
                cout<<"Size: "<<size<<endl;
                cout<<"Elements: ";
                while(!help.empty()){
                    cout<<help.top();
                    mainn.push(help.top());
                    help.pop();
                }
                cout<<endl;
                }
            }
        }
    }
}
