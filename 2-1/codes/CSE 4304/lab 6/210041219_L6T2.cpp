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
    int t_size=heapsize;
    for(int i=n;i>=2;i--){
        swapp(1,i);
        heapsize--;
        max_heapify(1);
    }
    heapsize=t_size;
}

int  heap_minimum(int n){
    return heap[1]*(-1);
}
int heap_extract_min(int n){
    int temp=heap[1];
    heap[1]=heap[heapsize];
    n--;
    heapsize--;
    max_heapify(1);
    return temp*(-1);
}
void min_heap_insert(int val,int idx){
   idx++;
   heap[idx]=val*(-1);
   heapsize++;
   swapp(1,idx);
   build_max_heap(idx);
}
void heap_decrease_key(int pos,int k){
    heap[pos]=(heap[pos]+k);
    build_max_heap(heapsize);
}
void heap_increase_key(int pos,int k){
    heap[pos]=(heap[pos]-k);
    build_max_heap(heapsize);
}
void print_heap(int l,int r){
    for(int i=l;i<=r;i++){
        cout<<heap[i]*(-1)<<" ";
    }
    cout<<endl;
}

int main(void){
    int idx=0,n;
    while(1){
        cin>>n;
        if(n==-1) break;
        else{
            idx++;
            heap[idx]=n*(-1);
            heapsize++;
        }
    }
    build_max_heap(idx);
    cout<<"MIN HEAP:"<<endl;
    print_heap(1, idx);
    while(1){
        cin>>n;
        if(n==0) break;
        else if(n==1){
            cout<<heap_minimum(idx)<<endl;
            print_heap(1,idx);
        }
        else if(n==2){
            cout<<heap_extract_min(idx)<<endl;
            idx--;
            print_heap(1,idx);
        }
        else if(n==3){
            int x;
            cin>>x;
            min_heap_insert(x, idx);
            idx++;
            print_heap(1,idx);
        }
        else if(n==4){
            int x,pos;
            cin>>pos>>x;
            heap_decrease_key(pos,x);
            print_heap(1,idx);
        }
        else if(n==5){
            int x,pos;
            cin>>pos>>x;
            heap_increase_key(pos,x);
            print_heap(1,idx);
        }

    }

}
