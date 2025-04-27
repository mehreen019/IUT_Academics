#include<bits/stdc++.h>
#include <fstream>
#include <windows.h>
using namespace std;

void bubbleSort( vector<int>& v){
    for(int i=0;i<v.size();i++){
        for(int j=0; j<v.size()-i;j++){
            if(v[j]>v[j+1]) swap(v[j], v[j+1]);
        }
    }
    //return v;
}

void selectionSort(vector<int>& v){
    for(int i=0;i<v.size();i++){
        int minn=i;
        for(int j=i+1;j<v.size();j++){
            if(v[j]<minn){ swap(minn, v[j]); }
        }
        swap(v[i], minn);
    }
}

void Merge(vector<int>& v, int lo, int mid, int hi){
/*int laSize= mid-lo+1;
    int raSize= hi-mid;

    vector<int> la,ra;
    for(int i=0;i<laSize;i++){
        la.push_back( v[lo+i] );
        //cout<<la[i]<<" ";
    }
    for(int i=0;i<raSize;i++){
        ra.push_back(v[mid+1+i]);
        //cout<<ra[i]<<" ";
    }


    int curLaIdx=0, curRaIdx=0, curAllIdx=0;
    while(curLaIdx<laSize && curRaIdx<raSize){
        if(la[curLaIdx]<=ra[curRaIdx]){
            v[curAllIdx]= la[curLaIdx];
            curLaIdx++;

        }
        else{
            v[curAllIdx]=ra[curRaIdx];
            curRaIdx++;
            //cout<<"ok";
        }
        curAllIdx++;
    }

    while(curLaIdx<laSize){
        v[curAllIdx]=la[curLaIdx];
        curAllIdx++;
        curLaIdx++;
    }
    while(curRaIdx<raSize){
        v[curAllIdx]=ra[curRaIdx];
        curAllIdx++;
        curLaIdx++;
    }
    cout<<"ok";*/
    int i=lo, j=mid+1;
    //vector<int> aux(v.size(), 0);
    int aux[v.size()];
    for(int k=lo; k<=hi;k++){
        aux[k]=v[k];
    }
    for(int k=lo;k<=hi;k++){
        if(i>mid) v[k]=aux[j++];
        else if(j>hi) v[k]=aux[i++];
        else if(aux[j]< aux[i]) v[k]=aux[j++];
        else v[k]=aux[i++];
    }

}

void mergeSort(vector<int>& v, int lo, int hi){
    if(hi<=lo) return;
    int mid = lo + (hi-lo)/2;
    mergeSort(v, lo, mid);
    mergeSort(v, mid+1, hi);
    Merge(v, lo, mid, hi);
}

int main(void){
    vector<int> v;
    int x, before, after, exec=750000;
    ifstream infile("random_numbers.txt");
    while(exec--){
        infile>>x;
        cout<<x<<" ";
        if(x==-1) break;
        v.push_back(x);
    }
    cout<<endl;
    /*before = GetTickCount();
    bubbleSort(v);
    after = GetTickCount();
    cout<<"time for bubble sort: "<< after- before<< endl;*/

    /*before = GetTickCount();
    selectionSort(v);
    after = GetTickCount();
    cout<<"time for selection sort: "<< after- before<< endl;*/

    before = GetTickCount();
    mergeSort(v, 0, v.size()-1);
    after = GetTickCount();
    cout<<"time for merge sort: "<< after- before<< endl;

    /*before = GetTickCount();
    sort(v.begin(), v.end());
    after = GetTickCount();
    cout<<"time for library sort: "<< after- before<< endl;*/


    /*for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }*/

}
