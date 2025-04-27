#include<iostream>
#include<queue>
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
queue<struct node*> q;

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

void print_list_inorder(struct node* temp,int data){

    if(temp->left!=NULL) print_list_inorder(temp->left, temp->data);
    cout<<temp->data<<"("<<data<<") ";
    if(temp->right!=NULL) print_list_inorder(temp->right, temp->data);
}

void print_list_preorder(struct node* temp,int data){
    cout<<temp->data<<"("<<data<<") ";
    if(temp->left!=NULL) print_list_preorder(temp->left, temp->data);
    if(temp->right!=NULL) print_list_preorder(temp->right, temp->data);
}

void print_list_postorder(struct node* temp,int data){

    if(temp->left!=NULL) print_list_postorder(temp->left, temp->data);
    if(temp->right!=NULL) print_list_postorder(temp->right, temp->data);
    cout<<temp->data<<"("<<data<<") ";
}

void print_list_levelorder(int data){

    struct node* temp=q.front();
    q.pop();
    int p=0;
    if(temp->parent!=NULL) p=temp->parent->data;
    cout<<temp->data<<"("<<p<<") ";
    if(temp->left!=NULL){q.push(temp->left);}
    if(temp->right!=NULL){q.push(temp->right);}
    if(!q.empty()) print_list_levelorder(temp->data);

}


void insert_after_node(int data){
    struct node* newnode = create_node(data);
    struct node* temp = head;

    while(temp!=NULL){
        if(data>temp->data && temp->right!=NULL){temp->idx++; temp=temp->right;}
        else if(data<temp->data && temp->left!=NULL){temp->idx++; temp=temp->left;}
        else break;
    }
    if(temp->data>data){
        temp->left=newnode;
    }
    else{
        temp->right=newnode;
    }
    newnode->parent=temp;
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
    while(1){
        cin>>n;
        if(n==1){
            print_list_inorder(head, 0);
            cout<<endl;
        }
        else if(n==2){
            print_list_preorder(head,0);
            cout<<endl;
        }
        else if(n==3){
            print_list_postorder(head,0);
            cout<<endl;
        }
        else if(n==4){
            q.push(head);
            print_list_levelorder(0);
            cout<<endl;
        }
        else break;
    }
}
