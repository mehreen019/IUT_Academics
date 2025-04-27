#include<iostream>
using namespace std;

struct node{
    struct node* next;
    struct node* prev;
    int data;
};

struct node* head = NULL;
struct node* tail = NULL;
int length=0;

node* create_node(int key){
    struct node* newnode = new node();
    newnode->data=key;
    newnode->next=NULL;
    newnode->prev=NULL;

    return newnode;
}

void insert_front(int key){
    struct node* newnode = create_node(key);

    length++;
    if(length==1) tail = newnode;
    else{
    newnode->next=head;
    head->prev=newnode;cout<<"ok";}
    head=newnode;
}

void insert_back(int key){
    struct node* newnode = create_node(key);

    if(tail==NULL){
        head=newnode;
    }
    else{
        tail->next=newnode;
    }
    length++;
    newnode->prev=tail;
    tail=newnode;
}

void print_list(){
    struct node* newnode1 = new node();
    struct node* newnode2 = new node();
    newnode1 = head;
    newnode2 = tail;
    cout<<"head: "<<head->data<<" tail: "<<tail->data<<endl<<"HEAD PRINT: ";
    while(newnode1!=NULL){
        cout<<newnode1->data<<" ";
        newnode1= newnode1->next;
    }
    cout<<endl<<"TAIL PRINT: ";
    while(newnode2!=NULL){
        cout<<newnode2->data<<" ";
        newnode2= newnode2->prev;
    }
    cout<<endl;
}

void insert_after_node(int key, int val){
    struct node* newnode = create_node(key);
    struct node* temp = head;

    while(temp->data!=val){
        temp=temp->next;
        if(temp->next==NULL) break;
    }
    if(temp->next==NULL && temp->data!=val) cout<<"value doesn't exist"<<endl;
    else{
    if(temp->next==NULL) tail=temp;
    newnode->next=temp->next;
    temp->next->prev=newnode;
    newnode->prev=temp;
    temp->next=newnode;
    length++;
    }
}

void update_node(int key, int val){
    struct node* newnode = create_node(key);
    struct node* temp = head;

    while(temp->data!=val){
        temp=temp->next;
        if(temp->next==NULL) break;
    }
    if(temp->next==NULL && temp->data!=val) cout<<"value doesn't exist"<<endl;
    else{
    temp->data=key;
    }
}

void remove_head(){
    struct node* temp1 = new node();
    temp1=head->next;
    temp1->prev=NULL;
    free(head);
    head=temp1;
    length--;

    if(length==0) tail=NULL;
}

void remove_element(int val){
    struct node* temp = head;
    struct node* temp1 = head;

    if(temp->data==val) remove_head();
    else{
    while(temp->next->data!=val){
        temp=temp->next;
        if(temp->next->next==NULL) break;
    }
    if(temp->next->next==NULL && temp->next->data!=val) cout<<"value doesn't exist"<<endl;
    else{
        temp1=temp->next;
        if(temp1->next==NULL) tail=temp;
        temp->next=temp1->next;
        if(temp1->next!=NULL) temp1->next->prev=temp;
        free(temp1);
        length--;
    }
    }
}

void remove_end(){
    struct node* temp1 = new node();
    temp1=tail->prev;
    temp1->next=NULL;
    free(tail);
    tail=temp1;
    length--;

    if(length==0) head=NULL;
}

int main(void){
    int x,n;
    while(1){
        cin>>x;
        if(x==1){
            cin>>n;
            insert_front(n);
            print_list();
        }
        else if(x==2){
            cin>>n;
            insert_back(n);
            print_list();
        }
        else if(x==3){
            int val;
            cin>>n>>val;
            insert_after_node(n,val);
            print_list();
        }
        else if(x==4){
            int val;
            cin>>n>>val;
            update_node(n,val);
            print_list();
        }
        else if(x==5){
            remove_head();
            print_list();
        }
        else if(x==6){
            cin>>n;
            remove_element(n);
            print_list();
        }
        else if(x==7){
            remove_end();
            print_list();
        }
        else if(x==-1) break;
    }
}
