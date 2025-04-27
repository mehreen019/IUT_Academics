#include<iostream>
using namespace std;
struct Node{
    int data;
    Node *prev, *next;
};
Node* getnode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void print(Node* f, Node* r){
    Node* t = fr;
    while(1){
        cout<<t->data<<" ";
        if(t->next) break;
        else t=t->next;
    }

}

int main(void){
    int n,sz=0;
    Node* fr = NULL;
    Node* rr = NULL;
    if(n==1){
        int num;
        cin>>num;
        if(sz!=0){
            Node* newnode = getnode(num);
            fr->prev=newnode;
            newnode->next=fr;
            fr=newnode;
        }
        else{
            fr=rr=newnode;
        }
        sz++;
        print(Node* fr, Node* rr);
    }
    else if(n==2){
        int num;
        cin>>num;
        if(sz!=0){
            Node* newnode = getnode(num);
            rr->next=newnode;
            newnode->prev=rr;
            rr=newnode;
        }
        else{
            fr=rr=newnode;
        }
        sz++;
    }
    else if(n==3){
        if(sz==0) cout<<"Underflow"<<endl;
        else{
        Node* t= fr;
        fr=fr->next;
        fr->prev=NULL;
        free(t);
        sz--;
        }
    }
    else if(n==4){
        if(sz==0) cout<<"Underflow"<<endl;
        else{
        Node* t= rr;
        rr=rr->prev;
        rr->next=NULL;
        free(t);
        sz--;
        }
    }
    else if(n==5){
        cout<<sz<<endl;
    }
}
