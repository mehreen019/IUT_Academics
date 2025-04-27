#include<iostream>
using namespace std;
struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
    int height;
    int left_sub;
    int right_sub;
    int b_fact;
};

node* create_node(int data){
    struct node* temp = new node();
    temp->left=NULL;
    temp->right=NULL;
    temp->parent=NULL;
    temp->data=data;
    temp->height=0;
    temp->left_sub=0;
    temp->right_sub=0;

    return temp;
}

struct node* root = NULL;
int tot_node = 0;

node* search_key(struct node* check, int data){
    //cout<<"ok";
    while(check!=NULL && check->data!=data){
        if(data<check->data) check=check->left;
        else check=check->right;
    }
    //cout<<check->data;
    return check;
}

node* insert_key(struct node* check, int data){
    //
    struct node* temp= create_node(data);
    temp->data=data;

    if(check==NULL){  root=temp;cout<<"ok"; return root;}
    else if(check->left==NULL && check->data>data){ check->left=temp; check->left_sub+=1; temp->parent=check; return temp; }
    else if(check->right==NULL && check->data<data){ check->right=temp; check->right_sub+=1; temp->parent=check; return temp; }

    if(data< check->data){ check->left_sub+=1; insert_key(check->left, data);}
    else{ check->right_sub+=1; insert_key(check->right, data);}
}

node* find_parent(struct node* check){
    int data=check->data;
    while(check!=NULL && data>=check->data){
        check=check->parent;
        //if(check!=NULL) cout<<check->data;
    }
    //cout<<"ok";
    return check;
}

void display(struct node* check){
    //cout<<"ok";
    int p=0;
    if(check->parent!=NULL) p=check->parent->data;
    if(check->left!=NULL) display(check->left);
    if(check!=NULL) cout<<check->data<<"("<<check->b_fact<<")"<<" ";
    if(check->right!=NULL) display(check->right);
}

int height(struct node* t){
    if(t==NULL) return -1;
    else return t->height;
}

int update_height(struct node* t){
    return max(height(t->left), height(t->right))+1;
}

int balance_factor(struct node* t){
    return height(t->left)-height(t->right);
}

void right_rotate(struct node* imb){
    cout<<"right_rotate"<<endl;

    struct node* heavy= imb->left;
    struct node* hr= heavy->right;

    if(imb==root) root=heavy;
    else if(imb->parent->left==imb){
        imb->parent->left=heavy;
    }
    else imb->parent->right=heavy;

    heavy->parent=imb->parent;
    heavy->right=imb;
    imb->parent=heavy;
    imb->left=hr;
    if(hr!=NULL) hr->parent=imb;

    struct node* nn=imb;
    while(nn!=NULL){
        nn->height=update_height(nn);
        nn=nn->parent;
    }
}

void left_rotate(struct node* imb){
    cout<<"left_rotate"<<endl;

    struct node* heavy= imb->right;
    struct node* hr= heavy->left;

    if(imb==root) root=heavy;
    else if(imb->parent->left==imb){
        imb->parent->left=heavy;
    }
    else imb->parent->right=heavy;

    heavy->parent=imb->parent;
    heavy->left=imb;
    imb->parent=heavy;
    imb->right=hr;
    if(hr!=NULL) hr->parent=imb;

    struct node* nn=imb;
    while(nn!=NULL){
        nn->height=update_height(nn);
        nn=nn->parent;
    }
}


void avl(struct node* t){
    struct node* nn=t;
    while(nn!=NULL){
        nn->height=update_height(nn);
        //cout<< nn->height <<" ";
        nn=nn->parent;
    }
    struct node* bal= t;
    while(bal!=NULL){
        bal->b_fact=balance_factor(bal);
        bal=bal->parent;
    }
}

int main(void){
    int n,x;
    while(1){
        cin>>n;
        if(n==-1) break;
        else{
            struct node* t = insert_key(root, n);
            cout<<"ok";
            avl(t);
            tot_node++;
            cout<<endl;
            display(root);
            cout<<endl;
        }
    }
}

