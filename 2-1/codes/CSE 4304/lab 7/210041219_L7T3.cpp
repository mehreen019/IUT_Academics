#include<iostream>
#include<vector>
#include<math.h>
#define maxx 2000

using namespace std;

struct node{
    struct node* left;
    struct node* right;
    struct node* parent;
    int data;
    int idx;
};

int length=0;
int tree[maxx]={0};
struct node* head = NULL;

node* create_node(int key){
    struct node* newnode = new node();
    newnode->data=key;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->parent=NULL;
    newnode->idx=0;


    return newnode;
}

void insert_front(int key){
    struct node* newnode = create_node(key);
    newnode->idx=1;
    tree[newnode->idx]=1;
    length++;
    head=newnode;
}

void print_list(struct node* temp,int data){
    cout<<temp->data<<"("<<data<<") ";
    if(temp->left!=NULL) print_list(temp->left, temp->data);
    if(temp->right!=NULL) print_list(temp->right, temp->data);
}

node* find_node(struct node* t, int val){
    if(t->data==val) return t;
    else if(t->left==NULL && t->right==NULL) return NULL;

    struct node* t1 = new node();
    struct node* t2 = new node();

    if(t->left!=NULL) t1=find_node(t->left, val);
    if(t->right!=NULL) t2=find_node(t->right, val);

    if(t1!=NULL) return t1;
    else if(t2!=NULL) return t2;
    else return NULL;
}

void insert_after_node(int data, int parent, int lrc){
    struct node* newnode = create_node(data);
    struct node* temp1 = head;
    struct node* temp2 = head;

    temp2 = find_node(head, parent);
    if(temp2==NULL) cout<<"error"<<endl;
    else{
    if(lrc==1){
        temp2->left=newnode;
        newnode->idx=(temp2->idx)*2;
        tree[newnode->idx]=1;
    }
    else{
        temp2->right=newnode;
        newnode->idx=(temp2->idx)*2+1;
        tree[newnode->idx]=1;
    }
    newnode->parent=temp2;
    length++;
    }
}

void freeup(struct node* t){
    if(t->left!=NULL) freeup(t->left);
    if(t->right!=NULL) freeup(t->right);

    tree[t->idx]=0;
    free(t);
    length--;
}

void removal(int val){
    struct node* temp = find_node(head, val);
    if(temp==NULL) cout<<"error"<<endl;
    else{
        if(temp->parent->left->data==val) temp->parent->left=NULL;
        else temp->parent->right=NULL;
        freeup(temp);
    }
}

int main(void){
    int n,x;
    cin>>n;
    int data,parent, lrc;
    while(n--){
        cin>>data>>parent>>lrc;
        if(parent==0){
            insert_front(data);
        }
        else{
            insert_after_node(data, parent, lrc);
        }
    }
    print_list(head, 0);
    cout<<endl;
    while(1){
        cin>>n;
        if(n==2){
            cin>>x;
            removal(x);
            print_list(head, 0);
            cout<<endl;
        }
        else if(n==3){
            cin>>x;
            struct node* temp = find_node(head, x);
            if(temp->data==NULL) cout<<"NOT PRESENT"<<endl;
            else{
                int l=0, r=0;
                if(temp->left!=NULL) l=temp->left->data;
                if(temp->right!=NULL) r=temp->right->data;
                cout<<"PRESENT"<<endl;
                cout<<"left("<<l<<") right("<<r<<")"<<endl;
            }
        }
        else if(n==4){
            int i=n*n;
            for(;i>=1;i--){
                if(tree[i]){
                    x=i;
                    break;
                }
            }
            cout<<"height: "<<floor(log2(x))<<endl;
        }
        else break;
    }
}
