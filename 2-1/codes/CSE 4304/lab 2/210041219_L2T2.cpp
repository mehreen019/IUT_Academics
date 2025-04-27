#include<iostream>
using namespace std;
int main(void){
    string s1,s2;
    cin>>s1>>s2;
    int len=0,bull=0,cow=0;
    int arr1[10]={0},arr2[10]={0};
    for(int i=0; ;i++){
        if(s1[i]=='\0') break;
        else len++;
    }
    for(int i=0;i<len;i++){
        if(s1[i]==s2[i]) bull++;
        arr1[s1[i]-'0']++;
        arr2[s2[i]-'0']++;
    }
    for(int i=0;i<10;i++){
        if(arr1[i] && arr2[i]){
            if(arr1[i]<=arr2[i]) cow+=arr1[i];
            else cow+=arr2[i];
        }
    }
    cout<<bull<<"B"<<cow-bull<<"C";
}
