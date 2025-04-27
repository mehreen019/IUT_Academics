#include<bits/stdc++.h>
using namespace std;
const int sz=200;
int arr[sz]={0},cou=0,prime=7;

void linear_probing(int ts, int n){
    int ty=0; //try attempt
    bool l=0;

    for(int i=0;i<ts;i++){
        ty++;
        int hv=(n+i)%ts; ///hash function
        if(arr[hv]==0){
            arr[hv]=n;
            cou++;
            double lf=(float)cou/ts; ///load factor
            cout<<"Inserted: index "<<hv<<" (load factor: "<<lf<<")"<<endl;
            break;
        }
        else{
            cout<<"Collision at: index "<<hv<<endl;
        }
        if(ty==6){
            cout<<"Input abandoned"<<endl;
            break;
        }
    }

}

void quadratic_probing(int ts, int n){
    int ty=0;
    bool l=0;

    for(int i=0;i<ts;i++){
        ty++;
        int hv=(n+(i*i))%ts;
        if(arr[hv]==0){
            arr[hv]=n;
            cou++;
            double lf=(float)cou/ts;
            cout<<"Inserted: index "<<hv<<" (load factor: "<<lf<<")"<<endl;
            break;
        }
        else{
            cout<<"Collision at: index "<<hv<<endl;
        }
        if(ty==6){
            cout<<"Input abandoned"<<endl;
            break;
        }
    }
}

void double_hashing(int ts, int n){
    int ty=0;
    bool l=0;

    for(int i=0;i<ts;i++){
        ty++;
        int hv=(n+(i*(prime-(n%prime))))%ts;
        if(arr[hv]==0){
            arr[hv]=n;
            cou++;
            double lf=(float)cou/ts;
            cout<<"Inserted: index "<<hv<<" (load factor: "<<lf<<")"<<endl;
            break;
        }
        else{
            cout<<"Collision at: index "<<hv<<endl;
        }
        if(ty==6){
            cout<<"Input abandoned"<<endl;
            break;
        }
    }

}

int main(void){
    int n,ts,q;
    while(1){
        cin>>n>>ts>>q;
        if(q==-1) break;
        int num;
        while(q--){
            cin>>num;
            if(n==1){
                linear_probing(ts,num);
            }
            else if(n==2){
                quadratic_probing(ts,num);
            }
            else{
                double_hashing(ts,num);
            }
        }
        memset(arr,0,sizeof(arr));
        cou=0;
    }
}
