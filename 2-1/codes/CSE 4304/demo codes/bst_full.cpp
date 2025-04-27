#include<iostream>
#include<queue>
using namespace std;
struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
    int idx;
    int left_sub=0; //left sub tree size
    int right_sub=0; //right sub tree size
};


///initializes all values via a function
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
struct node* lca = NULL;
int tot_node = 0;
queue<struct node*> q;


///basic search (iterative)
node* search_key(struct node* check, int data){
    while(check!=NULL && check->data!=data){
        if(data<check->data) check=check->left;
        else check=check->right;
    }
    return check;
}

///least common ancestor searching methods
/**
1.check if the data itself has been found
2. check if a node exists where both one value exists to the right and
the other to the left. first such value is the ancestor
3.else continue moving towards the common direction of the values
**/
node* search_ancestor(struct node* temp,int d1, int d2){

    if(temp->data==d1 || temp->data==d2) return temp;
    else{
        if(d1>temp->data && d2<temp->data) return temp;
        else if(d1<temp->data && d2>temp->data) return temp;
        else{
            if(d1>temp->data) return search_ancestor(temp->right, d1,d2);
            else return search_ancestor(temp->left,d1,d2);
        }
    }
}


///data insertion (recursive)
void insert_key(struct node* check, int data){
    struct node* temp= create_node(data);

    if(check==NULL){ root=temp; root->parent=NULL; return;}
    else if(check->left==NULL && check->data>data){ check->left=temp; check->left_sub+=1; temp->parent=check; return; }
    else if(check->right==NULL && check->data<data){ check->right=temp; check->right_sub+=1; temp->parent=check; return; }

    if(data< check->data){ check->left_sub+=1; insert_key(check->left, data);}
    else{ check->right_sub+=1; insert_key(check->right, data);}
}


///find parent
/** takes a node as input and tries to find it's parent.
if root, returns the node itself **/
node* find_parent(struct node* check){
    int data=check->data;
    while(check!=NULL && data>=check->data){
        check=check->parent;
    }
    return check;
}


///print tree in inorder, preorder, postorder,level order
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


///delete node from bst
void delete_node(struct node* check){
    struct node* zp = new node();
    zp= check->parent;

    ///leaf node
    if(check->left==NULL && check->right==NULL){

        if(zp->data>check->data) zp->left=NULL;
        else zp->right=NULL;
    }

    ///one child exists
    else if(check->left==NULL && check->right!=NULL){
        if(zp->data>check->data){
            zp->left=check->right;
            check->right->parent=zp;
        }
        else{
            zp->right=check->right;
            check->right->parent=zp;
        }
    }
    else if(check->left!=NULL && check->right==NULL){
        if(zp->data>check->data){
            zp->left=check->left;
            check->left->parent=zp;
        }
        else{
            zp->right=check->left;
            check->left->parent=zp;
        }
    }

    ///both childs exist
    /**  **/
    else{
        struct node* succ = check->right; //finds successor in right sub tree
        while(succ->left!=NULL){
            succ=succ->left; //left most element in right sub tree is successor
        }

        /* checks if the node to be deleted is in left or right sub tree
        of parent and assigns successor accordingly */
        if(zp->data>check->data){
            zp->left=check->right;
            check->right->parent=zp;
            succ->left=check->left;
            check->left->parent=succ;
        }
        else{
            zp->right=check->right;
            check->right->parent=zp;
            succ->left=check->left;
            check->left->parent=succ;
        }
    }
}


int main(void){
    int n,x;
    while(1){
        cin>>x;
        if(x==-1) break;
        else{
            //insert in bst one by one
            insert_key(root, x);
        }
    }
}
