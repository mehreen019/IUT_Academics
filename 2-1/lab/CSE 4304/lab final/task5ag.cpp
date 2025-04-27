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
int idx=1,ans=0;

node* search_key(struct node* check, int data){
    while(check!=NULL && check->data!=data){
        if(data<check->data) check=check->left;
        else check=check->right;
    }
    return check;
}

node* insert_key(struct node* check, int data){
    struct node* temp= create_node(data);
    temp->data=data;

    if(check==NULL){  root=temp; return root;}
    else if(check->left==NULL && check->data>data){ check->left=temp; check->left_sub+=1; temp->parent=check; return temp; }
    else if(check->right==NULL && check->data<data){ check->right=temp; check->right_sub+=1; temp->parent=check; return temp; }

    if(data< check->data){ check->left_sub+=1; insert_key(check->left, data);}
    else{ check->right_sub+=1; insert_key(check->right, data);}
}

void print_list_inorder(struct node* temp,int data){
    if(temp->left!=NULL) print_list_inorder(temp->left, data);
    if(temp->data==data){
        cout<<idx<<endl;
        ans=1;
    }
    else idx++;
    if(temp->right!=NULL) print_list_inorder(temp->right, data);
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

    struct node* heavy= imb->left;
    struct node* hr= heavy->right;

    //checks which side the imbalanced is on
    if(imb==root) root=heavy;
    else if(imb->parent->left==imb){
        imb->parent->left=heavy;
    }
    else imb->parent->right=heavy;

    //reassigns parent
    heavy->parent=imb->parent;
    heavy->right=imb;
    imb->parent=heavy;

    //assigns heavy child's right to imbalanced node's left
    imb->left=hr;
    if(hr!=NULL) hr->parent=imb;

    //updates height of all parents
    struct node* nn=imb;
    while(nn!=NULL){
        nn->height=update_height(nn);
        nn=nn->parent;
    }

    //updates balance factors
    struct node* bal= imb;
    while(bal!=NULL){
        bal->b_fact=balance_factor(bal);
        bal=bal->parent;
    }
}

void left_rotate(struct node* imb){

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
    struct node* bal= imb;
    while(bal!=NULL){
        bal->b_fact=balance_factor(bal);
        bal=bal->parent;
    }
}


void avl(struct node* t){
    struct node* nn=t;

    /* updates the heights of the most recently inserted node's parents */
    while(nn!=NULL){
        nn->height=update_height(nn);
        nn=nn->parent;
    }

    struct node* bal= t;
    while(bal!=NULL){
        bal->b_fact=balance_factor(bal);

        /* if balance factor is greater than 1 or less than -1, rotation is needed */
        if(bal->b_fact>1 && bal->left->data>t->data){
            right_rotate(bal);
            break;
        }
        else if(bal->b_fact>1 && bal->left->data<t->data){
            left_rotate(bal->left);
            right_rotate(bal);
            break;
        }
        else if(bal->b_fact<-1 && bal->right->data<t->data){
            left_rotate(bal);
            break;
        }
        else if(bal->b_fact<-1 && bal->right->data>t->data){
            right_rotate(bal->right);
            left_rotate(bal);
            break;
        }
        bal=bal->parent;
    }
}



int main(void){
    int n,x,q;
    cin>>n;
    while(n--){
        cin>>x>>q;
        if(x==1){
            struct node* temp= insert_key(root, q);
            avl(temp);
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
