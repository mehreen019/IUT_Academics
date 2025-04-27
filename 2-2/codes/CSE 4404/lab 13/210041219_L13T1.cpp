#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,id,deadline,profit,cou=0,totalProfit=0;
    cin>>n;
    vector<int>jobs(60,-1);
    for(int i=0;i<n;i++){
        cin>>id>>deadline>>profit;
        while(jobs[deadline]>profit && deadline>0){
            deadline--;
        }
        if(deadline>0)
            jobs[deadline]=max(jobs[deadline], profit);
    }
    for(int i=0;i<60;i++){
        if(jobs[i]!=-1){
            cou++;
            totalProfit+=jobs[i];
        }
    }
    cout<<cou<<" "<<totalProfit<<endl;

}
