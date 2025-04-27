#include<iostream>
using namespace std;
const int ALPHABET_SIZE=26;
string last="";
int cou=0;

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
        if(!cur->children[idx]){
            cur->children[idx]=create_node();
        }
        cur=cur->children[idx];
    }
    cur->endofWord=true;
}

bool Search(string s){
    struct tnode* cur = root;
    for(int i=0;i<s.size();i++){
        int idx=tolower(s[i])-'a';
        if(!cur->children[idx]){
            return false;
        }
        cur=cur->children[idx];
        //cout<<s[i];
    }
    //cout<<cur->endofWord<<"ok";
    return cur->endofWord;
}

void display(struct tnode* temp, char s[], int level){
    //cout<<s<<endl;
    if(temp->endofWord){
        s[level]='\0';
        cout<<s<<endl;
        last=s;
        cou++;
        if(cou==3){ return;}
    }
    for(int i=0;i<ALPHABET_SIZE;i++){
        if(temp->children[i]){
            s[level]=i+'a';
            //cout<<s;
            display(temp->children[i], s, level+1);
            if(cou>=3) break;
        }
    }
}

void suggestions(string tos, char s[], int level){
    struct tnode* cur = root;
    //cout<<tos;
    cou=0;
    last="";
    for(int i=0;i<tos.size();i++){
        int idx=tolower(tos[i])-'a';
        //cout<<tos[i];
        if(!cur->children[idx]){
            //cout<<tos[i]<<endl;
            return;
        }
        s[level+i]=tos[i];

        //
        if(cur->endofWord){
            cout<<s<<" ";
            last=s;
            cou++;
            if(cou==3) return;
        }
        cur=cur->children[idx];

        //cout<<tos.size()<<i<<endl;
    }
    //cout<<cou;
    display(cur, s, level+tos.size());
}


int main(void){
    string s,tos="";
    int n,cou=0;
    cin>>n;
    char e[200];
    while(n--){
        cin>>s;
        Insert(s);
    }
    cin>>s;

    for(int i=0;i<s.size();i++){
        tos+=s[i];
        //cout<<tos;
        suggestions(tos,e,0);
        cou=0;
        if(last=="") cout<<"NULL"<<endl;
        //cout<<cou;
        /*while(--cou){
            cout<<last<<endl;
        }*/
    }
}

