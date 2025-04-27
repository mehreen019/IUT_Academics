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
int tot_node = 0;

int search_key(struct node* temp,int d1, int d2){

    if(temp->data==d1 || temp->data==d2) return temp->data;
    else{
        if(d1>temp->data && d2<temp->data) return temp->data;
        else if(d1<temp->data && d2>temp->data) return temp->data;
        else{
            if(d1>temp->data) return search_key(temp->right, d1,d2);
            else return search_key(temp->left,d1,d2);
        }
    }
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
    cin>>n;
    while(n--){
        cin>>x;
                insert_key(root, x);
                tot_node++;
    }
    cin>>n;
    while(n--){
        int p,q;
        cin>>p>>q;
        cout<<search_key(root,p,q)<<endl;
    }
}
