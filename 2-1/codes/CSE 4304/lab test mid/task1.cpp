#include<bits/stdc++.h>
using namespace std;
struct node{
    int val;
    node* right;
    node* left;
};
struct node* root= NULL;

struct node* init(int key){
    struct node* temp= new node;
    temp->val=key;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

void create_bst(int key){
    struct node* temp= init(key);
    if(root==NULL){ root=temp; }
    else{
        struct node* t= root;
        while(t!=NULL){
            if(key<t->val){
                if(t->left==NULL) break;
                else t=t->left;
            }
            else{
                if(t->right==NULL) break;
                else t=t->right;
            }
        }
        if(key<t->val){
            t->left=temp;
        }
        else t->right=temp;
    }
}

void preorder(struct node* cur){
    if(cur->right!=NULL) preorder(cur->right);
    if(cur->left!=NULL) preorder(cur->left);
    cout<<cur->val<<endl;
}

int main(void){
    stack<int> st;
    int n,x;
    cin>>n;
    while(n--){
        cin>>x;
        st.push(x);
    }
    while(!st.empty()){
        create_bst(st.top());
        st.pop();
    }
    preorder(root);
}
