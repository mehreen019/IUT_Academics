#include<iostream>
using namespace std;

struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
    int idx;
};

int length=0;
struct node* head = NULL;

node* create_node(int key){
    struct node* newnode = new node();
    newnode->data=key;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->parent=NULL;
    newnode->idx=0;


    return newnode;
}

void insert_front(int key){
    struct node* newnode = create_node(key);
    newnode->idx=0;
    head=newnode;
}

void print_list(struct node* temp,int data){
    cout<<temp->data<<"("<<data<<") ";
    if(temp->left!=NULL) print_list(temp->left, temp->data);
    if(temp->right!=NULL) print_list(temp->right, temp->data);
}

node* find_node(struct node* check, int data){
     while(check!=NULL && check->data!=data){
        if(data<check->data) check=check->left;
        else check=check->right;
    }
    //cout<<check->data;
    return check;
}

void insert_after_node(int data){
    struct node* newnode = create_node(data);
    struct node* temp = head;

    while(temp!=NULL){
        if(data>temp->data && temp->right!=NULL){temp=temp->right;}
        else if(data<temp->data && temp->left!=NULL){temp=temp->left;}
        else break;
    }
    if(temp->data>data){
        temp->left=newnode;
    }
    else{
        temp->right=newnode;
    }
    newnode->parent=temp;

    while(temp->parent!=NULL){
        int l=-1,r=-1;
        if(temp->left!=NULL) l=temp->left->idx;
        if(temp->right!=NULL) r=temp->right->idx;
        temp->idx=max(l,r)+1;
        temp=temp->parent;
    }
    if(temp==head){
        int l=-1,r=-1;
        if(temp->left!=NULL) l=temp->left->idx;
        if(temp->right!=NULL) r=temp->right->idx;
        temp->idx=max(l,r)+1;
    }
}

int main(void){
    int n,x;
    cin>>n;
    int data,l=0;
    while(n--){
        cin>>data;
        if(l==0){
            insert_front(data);
            l++;
        }
        else{
            insert_after_node(data);
        }
    }
    print_list(head, 0);
    cout<<endl;
    while(1){
        cin>>n;
        if(n==2){
            print_list(head, 0);
            cout<<endl;
        }
        else if(n==3){
            cin>>x;
            struct node* temp = find_node(head, x);
            if(temp==NULL) cout<<"NOT PRESENT"<<endl;
            else{
                int l=0, r=0, p=0;
                if(temp->left!=NULL) l=temp->left->data;
                if(temp->right!=NULL) r=temp->right->data;
                if(temp->parent!=NULL)  p=temp->parent->data;
                cout<<"PRESENT"<<endl;
                cout<<"parent("<<p<<") left("<<l<<") right("<<r<<")"<<endl;
            }
        }
        else if(n==4){
            cin>>x;
            struct node* temp = find_node(head, x);
            cout<<temp->idx<<endl;
        }
        else break;
    }
}
