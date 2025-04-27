#include<iostream>
#define maxx 200000
using namespace std;

int heap[maxx];
int heapsize=0;

void swapp(int i1, int i2){
    int temp=heap[i1];
    heap[i1]=heap[i2];
    heap[i2]=temp;
}

void max_heapify(int idx){
    int largest=idx;
    int left_child=2*idx;
    int right_child=2*idx+1;

    if(left_child<=heapsize && heap[left_child]>heap[idx]){
        largest=left_child;
    }
    if(right_child<=heapsize && heap[right_child]>heap[largest]){
        largest=right_child;
    }
    if(idx!=largest){
        swapp(idx,largest);
        max_heapify(largest);
    }
}
void build_max_heap(int n){
    for(int i=n/2;i>=1;i--){
        max_heapify(i);
    }
}
void heap_sort(int n){
    build_max_heap(n);
    for(int i=n;i>=2;i--){
        swapp(1,i);
        heapsize--;
        max_heapify(1);
    }
}


int main(void){
    int idx=0,n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>heap[i];
    }
    heapsize=n;
    heap_sort(n);
    if(n%2) cout<<heap[n/2]<<endl;
    else{
        cout<<((float)heap[n/2]+(float)heap[(n/2)+1])/2.00<<endl;
    }

}
