///summing tree with lazy propogation

#include <iostream>
#define maxx 200010
#define ll long long
using namespace std;

const int MAX  = (1e9 + 10);
int arr[maxx];
int segment[maxx * 3]={0};
ll lazy[maxx * 3]={0};
void init(ll node, ll b, ll e)
{
    if (b==e) {
        segment[node] = arr[b];
        return;
    }
    int Left = node * 2;
    int Right = node * 2 + 1;
    int mid = (b + e) / 2;
    init(Left, b, mid);
    init(Right, mid + 1, e);
    segment[node] = (segment[Left] + segment[Right]);
}

///query without lazy propagation (within range)
ll query(ll node, ll b, ll e, ll i, ll j)
{
    if (i > e || j < b)
        return MAX;
    if (b >= i && e <= j)
        return segment[node];
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e) / 2;
    return (query(left, b, mid, i, j) + query(right, mid + 1, e, i, j));
}

ll Find(ll x, ll node){
    if(segment[node]<x) return MAX;

    ll cur=segment[node];
    ll left = node * 2;
    ll right = node * 2 + 1;
    if(x<=segment[left]){
        cur=min(cur, Find(x, left));
    }
    else if(x<=segment[right]){
        cur=min(cur, Find(x, right));
    }
    return cur;
}

///updating within a range without lazy (single value)
void update(ll node, ll b, ll e, ll i, ll newvalue)
{
    if (i>e||i<e)
        return;
    if (b>=i && e<=i) {
        segment[node] = newvalue;
        return;
    }
    ll Left = node * 2;
    ll Right = node * 2 + 1;
    ll mid = (b + e) / 2;
    update(Left, b, mid, i, newvalue);
    update(Right, mid + 1, e, i, newvalue);
    segment[node] = (segment[Left] + segment[Right]);
}

///query with lazy (single value)
ll lazy_query(ll node, ll b, ll e, ll i)
{
    if(lazy[node]!=0){
        segment[node]+=(e-b+1)*lazy[node]; //unless leaf node, update segment node with entire range of the lazy node

        //passing the current lazy node's pending to it's children
        if(b!=e){
            ll left=node*2;
            ll right=node*2+1;
            lazy[left]+=lazy[node];
            lazy[right]+=lazy[node];
        }
        lazy[node]=0;
    }
    if (i > e || i < b)
        return 0;
    if (b >= i && e <= i)
        return segment[node];
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e) / 2;
    ll q1=lazy_query(left, b, mid, i);
    ll q2=lazy_query(right, mid + 1, e, i);
    return q1+q2;
}

///updating with lazy (within a range)
void lazy_update(ll node, ll b, ll e, ll i,ll j, ll newvalue)
{
    if(lazy[node]!=0){
        segment[node]+=(e-b+1)*lazy[node];
        if(b!=e){
            ll left=node*2;
            ll right=node*2+1;
            lazy[left]+=lazy[node];
            lazy[right]+=lazy[node];
        }
        lazy[node]=0;
    }
    if (i > e || j < b || b>e)
        return;
    if (b >= i && e <= j) {
        segment[node] += (e-b+1)*newvalue; //updates the current node, and passes value to lazy children
        if(b!=e){
            lazy[node*2]+=newvalue;
            lazy[node*2 +1]+=newvalue;
        }
        return;
    }
    ll Left = node * 2;
    ll Right = node * 2 + 1;
    ll mid = (b + e) / 2;
    lazy_update(Left, b, mid, i,j, newvalue);
    lazy_update(Right, mid + 1, e, i,j, newvalue);
    segment[node] = (segment[Left] + segment[Right]);
}


int main()
{
    ll n, q,x,a,b,newval;
    cin >> n>>q;
    for(ll i = 1; i <= n; i++) cin >> arr[i];
    init(1, 1, n);

    while(q--)
    {
        cin>>x>>a;
        if(x==1)
        {
            cin>>b>>newval;
            lazy_update(1,1,n,a,b,newval);
        }
        else{
            cout<<lazy_query(1,1,n,a)<<endl;
        }
    }
    return 0;
}
