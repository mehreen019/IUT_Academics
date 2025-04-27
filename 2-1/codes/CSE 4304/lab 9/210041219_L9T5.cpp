#include<iostream>
using namespace std;
struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
    int left_sub=0;
    int right_sub=0;
};

struct node* root = NULL;
struct node* lca = NULL;
int tot_node = 0;

node* search_an(struct node* temp,int d1, int d2){

    if(temp->data==d1 || temp->data==d2) return temp;
    else{
        if(d1>temp->data && d2<temp->data) return temp;
        else if(d1<temp->data && d2>temp->data) return temp;
        else{
            if(d1>temp->data) return search_an(temp->right, d1,d2);
            else return search_an(temp->left,d1,d2);
        }
    }
}

void print_left(struct node* temp, int d){

    if(d<temp->data) print_left(temp->left,d);
    else if(d>temp->data) print_left(temp->right,d);
    cout<<temp->data<<" ";
    tot_node++;
    //if(d==temp->data) return;
}

void print_right(struct node* temp, int d){
    if(temp!=lca){ cout<<temp->data<<" ";
                    tot_node++;}
    if(d>temp->data) print_right(temp->right,d);
    else if(d<temp->data) print_right(temp->left,d);
    //if(d==temp->data) return;
}

void insert_key(struct node* check, int data){
    //cout<<"ok";
    struct node* temp= new node();
    temp->data=data;

    if(check==NULL){ root=temp; root->parent=NULL; return;}
    else if(check->left==NULL && check->data>data){ check->left=temp; check->left_sub+=1; temp->parent=check; return; }
    else if(check->right==NULL && check->data<data){ check->right=temp; check->right_sub+=1; temp->parent=check; return; }

    if(data< check->data){ check->left_sub+=1; insert_key(check->left, data);}
    else{ check->right_sub+=1; insert_key(check->right, data);}
}

void display(struct node* check){
    //cout<<"ok";
    if(check->left!=NULL) display(check->left);
    if(check!=NULL) cout<<check->data<<" ";
    if(check->right!=NULL) display(check->right);
}


int main(void){
    int n,x;
    while(1){
        cin>>x;
        if(x==-1) break;
        else{
            insert_key(root, x);
        }
    }
    while(1){
        int p,q;
        cin>>p>>q;
        lca = search_an(root,p,q);
        print_left(lca, p);
        print_right(lca,q);
        cout<<endl<<tot_node<<endl;
        tot_node=0;
    }
}
