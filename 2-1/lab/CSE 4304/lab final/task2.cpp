#include<bits/stdc++.h>
using namespace std;
const int ALPHABET_SIZE=10;

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

struct tnode* root=create_node();

void Insert(string s){
    struct tnode* cur = root;
    for(int i=0;i<s.size();i++){

        if(!cur->children[s[i]-'0']){
            cur->children[s[i]-'0']=create_node();
        }

        cur=cur->children[s[i]-'0'];
    }
    cur->endofWord=true;
}

bool Search(string s){
    struct tnode* cur = root;
    for(int i=0;i<s.size();i++){
        if(!cur->children[s[i]-'0']){
            return false;
        }
        else if(cur->children[s[i]-'0']->endofWord){
            return true;
        }
        cur=cur->children[s[i]-'0'];
    }
    return cur->endofWord;
}

void freeup(struct tnode* temp){
    for(int i=0;i<ALPHABET_SIZE;i++){
        if(temp->children[i]){
            freeup(temp->children[i]);

        }
        cout<<i<<" ";
        free(temp->children[i]);
    }
}


int main(void){
    int tst,ortst;
    cin>>tst;
    ortst=tst;
    while(tst--){
        string s;
        int n;
        cin>>n;
        bool ans=1;
        while(n--){
            cin>>s;
            if(Search(s)){
                ans=0;
                //cout<<"ok";
            }
            else Insert(s);
        }
        cout<<"Case "<<ortst-tst<<": ";
        if(ans){
            cout<<"YES"<<endl;
        }
        else cout<<"NO"<<endl;
        freeup(root);
        //cout<<"ok";
    }
}
