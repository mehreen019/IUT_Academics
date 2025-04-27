#include<bits/stdc++.h>
using namespace std;

class controller{
public:
    map<int, pair<string, string>> m;
    user u[100];
};

struct reminder{

};

class user{
private:
    string name;
    string email;
public:
    struct reminder r[100];
};

class note : public user{
public:
    FILE* note;
};

class workspace{
public:
    note n[100];
};

int main(void){}
