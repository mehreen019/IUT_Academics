#include<iostream>
using namespace std;
int main(void){
    int n,r;
    cin>>n>>r;
    int pow[n],rou[r];
    for(int i=0;i<n;i++){
        cin>>pow[i];
    }
    for(int i=0;i<r;i++){
        cin>>rou[i];
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(pow[i]>pow[j]){
                int temp=pow[i];
                pow[i]=pow[j];
                pow[j]=temp;
            }
        }
    }
    for(int i=0;i<r;i++){
        int cou=0,tot=0;
        for(int j=0;j<n;j++){
            if(pow[j]<=rou[i]){
                cou++;
                tot=tot+pow[j];
            }
            else break;
        }
        cout<<cou<<" "<<tot<<endl;
    }
}
