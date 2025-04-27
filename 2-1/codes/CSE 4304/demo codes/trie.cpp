///Lab 10 task 3

#include<iostream>
using namespace std;
const int ALPHABET_SIZE=26;

struct tnode{
    struct tnode* children[ALPHABET_SIZE];
    bool endofWord;
};

tnode* create_node(){
    struct tnode* temp= new tnode();
    for(int i=0;i<ALPHABET_SIZE;i++){
        temp->children[i]=NULL;
    }
    temp->endofWord=false;
    return temp;
}

struct tnode* root = create_node();

void Insert(string s){
    struct tnode* cur = root;
    for(int i=0;i<s.size();i++){
        int idx=tolower(s[i])-'a';

        //if the word doesn't already have a node associated, declare one
        if(!cur->children[idx]){
            cur->children[idx]=create_node();
        }

        //proceed through the length of the string
        cur=cur->children[idx];
    }

    //mark end of each word
    cur->endofWord=true;
}

bool Search(string s){
    struct tnode* cur = root;
    for(int i=0;i<s.size();i++){
        int idx=tolower(s[i])-'a';

        //if the character doesn't already have a node associated to it, it means this character has never occured,
        //thus this word doesn;t exist
        if(!cur->children[idx]){
            return false;
        }
        cur=cur->children[idx];
    }
    return cur->endofWord;
}

void display(struct tnode* temp, char s[], int level){
    //breaking condition if endofWord is reached
    if(temp->endofWord){
        s[level]='\0';
        cout<<s<<endl;
    }

    //otherwise look for all possible existing characters
    for(int i=0;i<ALPHABET_SIZE;i++){
        if(temp->children[i]){
            //assign current character to ith word (current level)
            s[level]=i+'a';

            //increase level for the next possible word
            display(temp->children[i], s, level+1);
        }
    }
}

int main(void){
    string s;
    int n;
    cin>>n;
    char e[200];
    while(n--){
        cin>>s;
        Insert(s);
    }
    display(root,e,0);
    cin>>n;
    while(n--){
        cin>>s;
        if(Search(s)) cout<<"T"<<endl;
        else cout<<"F"<<endl;
    }
}
