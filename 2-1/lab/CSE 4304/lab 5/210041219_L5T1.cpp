#include<iostream>
#include<stack>
#include<deque>
#include<vector>
using namespace std;
int main(void){
int scene=1;
while(1){
    int n,m,tot_m=0;
    cin>>n;
    if(n==0) break;
    int arr[n+1];
    vector<string> tomatch;
    string s,num;
    stack<string> help;
    deque<string> master,ans;
    arr[0]=0;
    for(int i=1;i<=n;i++){
        cin>>m;
        tot_m+=m;
        arr[i]=tot_m;
        for(int i=0;i<m;i++){
            cin>>s;
            tomatch.push_back(s);
        }
    }
    while(1){
        cin>>s;
        if(s=="ENQUEUE"){
            cin>>num;
            int idx=-1;
            for(int i=0;i<tomatch.size();i++){
                if(num==tomatch[i]) idx=i;
            }
            int i;
            for(i=1;i<=n;i++){
                if(idx<arr[i]){
                    idx=arr[i];
                    break;
                }
            }
            //cout<<idx<<endl;
            bool l=0;
            if(master.empty()) master.push_front(num);
            else{
            i=arr[i-1];
            while(!(master.empty()) && i<idx){
                if(master.front()==tomatch[i]){
                    help.push(master.front());
                    master.pop_front();
                    l=1;

                }
                i++;
               // cout<<master.front()<<endl;
            }
            if(l){
                master.push_front(num);
                while(!(help.empty())){
                    master.push_front(help.top());
                    help.pop();
                }
            }
            else{
                master.push_back(num);
            }
            }
        }
        else if(s=="DEQUEUE"){
            ans.push_back(master.front());
            master.pop_front();
        }
        else if(s=="STOP"){
            cout<<"SCENARIO "<<scene<<endl;
            while(!(ans.empty())){
                cout<<ans.front()<<endl;
                ans.pop_front();
            }
            scene++;
        }
    }
}
}
