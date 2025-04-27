#include<bits/stdc++.h>
using namespace std;
int main(void){
    int n,a,b,cou=0;
    cin>>n;
    vector<int>start(60,0);
    int r1[n],r2[n];
    vector<pair<int, pair<int,int> > > jobs;
    for(int i=0;i<n;i++){
        cin>>r1[i];
    }
    for(int i=0;i<n;i++){
        cin>>r2[i];
    }
    for(int i=0;i<n;i++){
        jobs.push_back({r2[i]-r1[i], {r1[i], r2[i]} } );
    }
    sort(jobs.begin(), jobs.end());

    for(int i=0;i<n;i++){
        pair<int,int> it=jobs[i].second;
        bool ans=1;
        for(int j=it.first;j<=it.second;j++){
            if(start[j]!=0){ ans=0; break;}
            start[j]++;
        }
         if(ans) cou++;
    }
    cout<<cou<<endl;

}
