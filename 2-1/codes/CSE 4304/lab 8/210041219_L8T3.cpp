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
int max_num= INT_MIN;

node* search_key(struct node* check, int data){
    //cout<<"ok";
    while(check!=NULL && check->data!=data){
        max_num=max(max_num, check->data);
        if(data<check->data) check=check->left;
        else check=check->right;
    }
    //cout<<check->data;
    if(check!=NULL) max_num=max(max_num, check->data);
    return check;
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

node* find_node(struct node* check, int data){
    while(check->parent!=NULL && data>=check->parent->data){
        max_num=max(check->data, max_num);
        check=check->parent;
    }
    check=search_key(check, data);
    return check;
}

void display(struct node* check){
    //cout<<"ok";
    if(check->left!=NULL) display(check->left);
    if(check!=NULL) cout<<check->data<<" left tree: "<<check->left_sub<<" right tree: "<<check->right_sub<<endl;
    if(check->right!=NULL) display(check->right);
}

int main(void){
    int n,x1,x2;
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
                tot_node++;
            }
            display(root);
            cout<<endl;
        }
    }
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x1>>x2;
        struct node* cur = search_key(root, x1);
        max_num=0;
        struct node* ans= find_node(cur, x2);
        cout<<max_num<<endl;
    }
}
