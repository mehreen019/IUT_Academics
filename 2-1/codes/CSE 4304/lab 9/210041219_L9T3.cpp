#include<iostream>
#include<queue>
using namespace std;
struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
    int idx;
    int left_sub=0;
    int right_sub=0;
};

node* create_node(int key){
    struct node* newnode = new node();
    newnode->data=key;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->parent=NULL;
    newnode->idx=0;
    newnode->left_sub=0;
    newnode->right_sub=0;

    return newnode;
}

struct node* root = NULL;
int tot_node = 0;
int h=0;
queue<struct node*> q;


void search_key(){

    struct node* temp=q.front();
    int l=0, r=0;

    q.pop();
    if(temp->left!=NULL){q.push(temp->left); l=temp->left->idx;}
    if(temp->right!=NULL){q.push(temp->right); r=temp->right->idx;}
    h=max(h,  l+ r+ 3);
    if(!q.empty()) search_key();

}

void insert_front(int key){
    struct node* newnode = create_node(key);
    newnode->idx=0;
    root=newnode;
}

void insert_after_node(int data){
    struct node* newnode = create_node(data);
    struct node* temp = root;

    while(temp!=NULL){
        if(data>temp->data && temp->right!=NULL){temp->right_sub+=1; temp=temp->right;}
        else if(data<temp->data && temp->left!=NULL){temp->left_sub+=1; temp=temp->left;}
        else break;
    }
    if(temp->data>data){
        temp->left=newnode;
        temp->left_sub+=1;
    }
    else{
        temp->right=newnode;
        temp->right_sub+=1;
    }
    newnode->parent=temp;

    while(temp->parent!=NULL){
        int l=-1,r=-1;
        if(temp->left!=NULL) l=temp->left->idx;
        if(temp->right!=NULL) r=temp->right->idx;
        temp->idx=max(l,r)+1;
        temp=temp->parent;
    }
    if(temp==root){
        int l=-1,r=-1;
        if(temp->left!=NULL) l=temp->left->idx;
        if(temp->right!=NULL) r=temp->right->idx;
        temp->idx=max(l,r)+1;
    }
}

void display(struct node* check){
    //cout<<"ok";
    if(check->left!=NULL) display(check->left);
    if(check!=NULL) cout<<check->data<<" "<<check->left_sub<<" "<<check->right_sub<<" "<<check->idx<<endl;
    if(check->right!=NULL) display(check->right);
}


int main(void){
    int n,x;
    cin>>n;
    int l=0;
    while(n--){
        cin>>x;
        if(l==0){
            insert_front(x);
            l++;
        }
        else{
            insert_after_node(x);
        }
        tot_node++;
    }
    //display(root);
    q.push(root);
    search_key();
    cout<<h;
}

