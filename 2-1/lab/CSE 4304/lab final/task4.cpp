#include<iostream>
#include<queue>
using namespace std;
struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
};


///initializes all values via a function
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

void print_list_inorder(struct node* temp,int data){
    if(temp->left!=NULL) print_list_inorder(temp->left, data);
    if(temp->data==data){
        cout<<idx<<endl;
        ans=1;
        return;
    }
    else idx++;
    if(temp->right!=NULL) print_list_inorder(temp->right, data);
}



int main(void){
    int n,x,q;
    cin>>n;
    while(n--){
        cin>>x>>q;
        if(x==1){
            insert_key(root, q);
        }
        else{
            idx=1; ans=0;
            print_list_inorder(root,q);
            if(!ans){
                cout<<"Data tidak ada"<<endl;
            }
        }
    }
}
