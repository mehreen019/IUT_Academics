#include<bits/stdc++.h>
using namespace std;
int main(void){
    int tst,a,b;
    cin>>tst;
    while(tst--){
        cin>>a>>b; //cout<<"ok";
        int i=a,j=b,c=1,cou=0;
        if(a==b){cout<<0<<endl;}
        else{
        while(i!=j){
            i+=c; cou++;
            j-=c; cou++;
            c++;
            if(j<=i) break;
            //else if(i>j){ cou--; break; }
            else if(j-i<=c){ cou++; break; }

            //else if(j-i) break;45
            }
        cout<<cou<<endl;
        }
    }
}
//1 1 1 -3
//1 2 1 -4
//1 2 1 1 -5
//1 2 2 1 -6
//46 48 48 50
//45 46 48 49 51 52
//1 2 2 1 1 - 7
//1 2 2 2 1 - 8
//1 2 3 2 1 - 9
