#include<iostream>
#include<queue>
using namespace std;
struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
};


node* create_node(int key){
    struct node* newnode = new node();
    newnode->data=key;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->parent=NULL;
    return newnode;
}

struct node* root = NULL;
int idx=1,ans=0;


node* search_key(struct node* check, int data){
    while(check!=NULL && check->data!=data){
        if(data<check->data) check=check->left;
        else check=check->right;
    }
    return check;
}


void insert_key(struct node* check, int data){
    struct node* temp= create_node(data);

    if(check==NULL){ root=temp; root->parent=NULL; return;}
    else if(check->left==NULL && check->data>data){ check->left=temp;  temp->parent=check; return; }
    else if(check->right==NULL && check->data<data){ check->right=temp; temp->parent=check; return; }

    if(data< check->data){ insert_key(check->left, data);}
    else{ insert_key(check->right, data);}
}

void print_list_postorder(struct node* temp){

    if(temp->left!=NULL) print_list_postorder(temp->left);
    if(temp->right!=NULL) print_list_postorder(temp->right);
    cout<<temp->data<<" ";
}


int main(void){
    int n,x,q;
    cin>>n;
    int pre[n];
    int in[n];
    for(int i=0;i<n;i++){
        cin>>pre[i];
        insert_key(root, pre[i]);
    }
    for(int i=0;i<n;i++){
        cin>>in[i];
    }
    print_list_postorder(root);
}
