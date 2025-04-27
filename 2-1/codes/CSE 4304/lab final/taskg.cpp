#include<iostream>
#include<vector>
using namespace std;

struct node{
    struct node* next;
    int data;
};

struct node* root = NULL;
int idx=1,ans=0;
vector<int> deleted;


void search_key(struct node* check, int el){
    if(idx==el){
        deleted.push_back(check->data);
        root=check->next;
    }
    else{
        while(check!=NULL && idx+1!=el){
            check=check->next;
            idx++;
        }
        deleted.push_back(check->next->data);
        check->next=check->next->next;
    }
}


void insert_key(struct node* check, int data){
    struct node* temp= new node();
    temp->data=data;
    temp->next=NULL;

    if(check==NULL){ root=temp; return;}
    while(check->next!=NULL){
        check=check->next;
    }

    check->next=temp;
}


int main(void){
    int n,x,q,el;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
        insert_key(root, arr[i]);
    }
    for(int i=0;i<n;i++){
        idx=1;
        cin>>el;
        search_key(root, el);
    }
    for(int i=0;i<deleted.size();i++){
        cout<<deleted[i]<<" ";
    }
}
