#include<iostream>
using namespace std;
struct node{
    struct node* left;
    struct node* right;
    int data;
};

struct node* root = NULL;

bool search_key(struct node* check, int data){
    //cout<<"ok";

    if(check==NULL) return 0;
    else if(check->data<=data+3 && check->data>=data-3) return 1;


    if(data<check->data) return search_key(check->left, data);
    else if(data>check->data) return search_key(check->right, data);
}

void insert_key(struct node* check, int data){
    //cout<<"ok";
    struct node* temp= new node();
    temp->data=data;

    if(check==NULL){ root=temp; return;}
    else if(check->left==NULL && check->data>data){ check->left=temp; return; }
    else if(check->right==NULL && check->data<data){ check->right=temp; return; }

    if(data< check->data) insert_key(check->left, data);
    else insert_key(check->right, data);
}

void display(struct node* check){
    //cout<<"ok";
    if(check->left!=NULL) display(check->left);
    if(check!=NULL) cout<<check->data<<" ";
    if(check->right!=NULL) display(check->right);
}

int main(void){
    int n;
    while(1){
        cin>>n;
        if(n==-1) break;
        else{

            if(search_key(root, n)){
                cout<<"RESERVATION FAILED"<<endl;
            }
            else{
                //cout<<"ok";
                insert_key(root, n);
            }
            display(root);
            cout<<endl;
        }
    }
}
