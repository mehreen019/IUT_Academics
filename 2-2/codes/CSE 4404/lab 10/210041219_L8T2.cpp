#include<bits/stdc++.h>
using namespace std;
const int MAXX=2e5+7;
int main(void){
    int n,minLength,maxLength;
    cin>>n>>minLength>>maxLength;
    int r[n];
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    int maxsum=0, cou=0,sum=0,l=-1,h=-1,toDel=0;
    queue<int> q, help;
    for(int i=0;i<n;i++){
        cou++;
        if(cou<minLength){
            sum+=r[i];q.push(sum);
        }
        else if(cou>=minLength && cou<maxLength){
            sum+=r[i];
            q.push(sum);
            maxsum=max(sum, maxsum);
        }
        else if(cou==maxLength){
            sum+=r[i];
            maxsum=max(sum, maxsum);
            toDel=q.front();

            while(!q.empty()){
                //cout<<q.front()<<endl;
                maxsum=max(sum-q.front(), maxsum);
                if(q.front()!=toDel) help.push(q.front());
                q.pop();
            }
            while(!help.empty()){
                maxsum=max(help.front()-toDel, maxsum);
                q.push(help.front()-toDel);
                help.pop();
            }
            cou--;
            sum-=toDel;
        }
    }
    cout<<maxsum<<endl;
}
