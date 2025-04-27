#include<iostream>
#include<stack>
using namespace std;
int main(void){
    while(1){
    int n;
    cin>>n;
    if(n==0) break;
    int arr[n],minar=0,ar;
    stack<int> st;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    st.push(0);
    for(int i=1;i<n;i++){
        while(arr[st.top()]>arr[i]){
            int cou,temp=st.top();
            //cout<<"ok"<<endl;
            while(arr[st.top()]>=arr[temp]){
                cou=st.top();
                st.pop();
                //cout<<cou;
                if(st.empty()) break;
            }
            //if(st.empty)ar=(i-st.top())*arr[st.top()];
            //else

            ar=(i-cou)*arr[temp];
            minar=max(ar,minar);
            if(st.empty()) break;
        }
        st.push(i);
    }

    while(!st.empty()){
        int cou,temp=st.top(),i;
            //cout<<"ok"<<endl;
            while(arr[st.top()]>=arr[temp]){
                cou=st.top();
                st.pop();
                //cout<<cou;
                if(st.empty()) break;
            }
            //if(st.empty)ar=(i-st.top())*arr[st.top()];
            //else
            if(st.empty()){
                cou=0;
                ar=(n-cou)*arr[temp];
            }
            else{ cou=st.top();
            ar=(n-cou-1)*arr[temp];}
            minar=max(ar,minar);
            if(st.empty()) break;
    }
   /* while(!st.empty()){
        cout<<st.top()<<endl;
        st.pop();
    }*/
    cout<<minar<<endl;
    }
}
