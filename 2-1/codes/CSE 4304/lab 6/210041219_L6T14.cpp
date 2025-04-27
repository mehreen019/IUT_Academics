#include<iostream>
using namespace std;
int main(void){
    int n;
    cin>>n;
    int r[n];
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    int l1,l2,l3;
    if(n>=3){
    if(r[0]>=r[1]){
        if(r[0]>=r[2]){
            l1=r[0];
            if(r[1]>=r[2]){ l2=r[1];l3=r[2]; }
            else{ l2=r[2]; l3=r[1]; }
        }
        else { l1=r[2];l2=r[0];l3=r[1]; }
    }
    else if(r[0]>=r[2]){
        l1=r[1]; l2=r[0]; l3=r[2];
    }
    else{
        l3=r[0];
        if(r[1]>=r[2]){ l1=r[1];l2=r[2]; }
        else{ l1=r[2]; l2=r[1]; }
    }
    cout<<-1<<endl<<-1<<endl<<l1*l2*l3<<endl;
    for(int i=3;i<n;i++){
        if(r[i]>l1){
            l3=l2; l2=l1; l1=r[i];
        }
        else if(r[i]>l2){
            l3=l2; l2=r[i];
        }
        else if(r[i]>l3) l3=r[i];
        cout<<l1*l2*l3<<endl;
    }
    }
    else{
        for(int i=0;i<n;i++){
            cout<<-1<<endl;
        }
    }
}
