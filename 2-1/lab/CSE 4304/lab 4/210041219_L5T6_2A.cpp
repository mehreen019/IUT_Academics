#include<iostream>
#include<queue>
using namespace std;
int main(void){
    int n,x,curn=0;
    queue<int> student, sandwich;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x;
        student.push(x);
    }
    for(int i=0;i<n;i++){
        cin>>x;
        sandwich.push(x);
    }
    while(1){
        if(sandwich.front()==student.front()){
            sandwich.pop();
            student.pop();
            curn=0;
            n--;
        }
        else{
            student.push(student.front());
            student.pop();
            curn++;
        }
        if(curn==n) break;
    }
    cout<<curn<<endl;
}
