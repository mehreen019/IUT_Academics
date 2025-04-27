//run korena
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    char c;
    int n;
    struct node *left, *right;
}node;

typedef struct heap{
    size_t size;
    size_t cap;
    struct node** arr;//node** arr==node* arr[size]
}heap;

node* newnode(char name, int num){
    node* nod=(node*)malloc(sizeof(node));
    nod->left= nod->right= NULL;
    nod->c= name;
    nod->n= num;
    return nod;
}

void swap(node* a, node* b){
    node* t=a;
    a=b;
    b=t;
}

void minheapify(heap* h, int i){
	int smol = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < h->size && h->arr[left]->n< h->arr[smol]->n)
		smol = left;
	if (right < h->size && h->arr[right]->n< h->arr[smol]->n)
		smol = right;
	if (smol != i) {
		swap(h->arr[smol], h->arr[i]);
		minheapify(h, smol);
	}
}

heap* openspace(size_t size){
    heap* h=(heap*)malloc(sizeof(heap*));
    h->size=0;
    h->cap=size;
    h->arr=(node**)malloc(h->cap*sizeof(node*));
    return h;
}

heap* buildheap(char name[],int num[], int size){
    heap* h=openspace(size);
    for(int i=0;i<size;i++){
        h->arr[i]=newnode(name[i],num[i]);
    }
    h->size=size;
    int n=size-1;
    for(int i=(n-1)/2;i>=0;i--){
        minheapify(h, i);
    }
}

node* extractnode(heap* h){
    node* t=h->arr[0];
    h->arr[0]=h->arr[h->size-1];
    h->size--;
    minheapify(h,0);
    return t;
}

int parent(int i){ return (i-1)/2; }

void insertnode(heap* h, node* t){
    h->arr[h->size++]=t;
    int i=h->size-1;
    while(i!=0 && h->arr[parent(i)]->n > h->arr[i]->n){
        swap(h->arr[parent(i)], h->arr[i]);
        i=parent(i);
    }
}

node* buildtree(char name[],int num[],int size){
    node *left,*right,*top;
    heap* minheap=buildheap(name, num, size);
    while(minheap->size!=1){
        left=extractnode(minheap);
        right=extractnode(minheap);
        top=newnode('!', left->n+right->n);
        top->left=left;
        top->right=right;
        insertnode(minheap, top);
    }
    return extractnode(minheap);
}

void printArr(int arr[], int n){
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);
	printf("\n");
}

int isLeaf(node* root){
	return !(root->left) && !(root->right);
}

void printtree(node* root, int arr[], int top){
    if (root->left) {
		arr[top] = 0;
		printtree(root->left, arr, top + 1);
	}
	if (root->right) {
		arr[top] = 1;
		printtree(root->right, arr, top + 1);
	}
	if (isLeaf(root)) {
		printf("%c: ", root->c);
		printArr(arr, top);
	}
}

void huffman(name, num, size){
    node* root=buildtree(name, num, size);
    int arr[100], top=0;
    printtree(root, arr, top);
}

int main(void){
    char name[] = { 'm', 'e', 'h', 'r', 'n', 'o', 's', 'a', 'i', 'c', 'w', 'd', 'y', 'u' };
	int num[] = { 1,3,4,2,2,2,2,1,1,1,1,1,1,1};

	int size = sizeof(name) / sizeof(name[0]);
	huffman(name, num, size);
}
