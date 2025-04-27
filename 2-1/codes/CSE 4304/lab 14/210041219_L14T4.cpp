#include <iostream>
#define maxx 2005000
#define ll long long
using namespace std;

const int MAX  = 1e9 + 10;
ll arr[maxx];
ll segment[maxx * 3]={0};
ll lazy[maxx * 3]={0};
void init(ll node, ll b, ll e)
{
    if (b==e) {
        segment[node] = arr[b];
        return;
    }
    ll Left = node * 2;
    ll Right = node * 2 + 1;
    ll mid = (b + e) / 2;
    init(Left, b, mid);
    init(Right, mid + 1, e);
    segment[node] = (segment[Left] +segment[Right]);
}
ll query(ll node, ll b, ll e, ll i)
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
    if (i > e || i < b)
        return 0;
    if (b >= i && e <= i)
        return segment[node];
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e) / 2;
    ll q1=query(left, b, mid, i);
    ll q2=query(right, mid + 1, e, i);
    return q1+q2;
}
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
        segment[node] += (e-b+1)*newvalue;
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
    /*for(int i = 1; i <= n*3; i++){
        cout<<segment[i]<<" ";
    }*/
    while(q--)
    {
        cin>>x>>a;
        if(x==1)
        {
            cin>>b>>newval;
            lazy_update(1,1,n,a,b,newval);
            /*for(int i = 1; i <= n*3; i++){
                cout<<segment[i]<<" ";
            }*/
        }
        else{
            cout<<query(1,1,n,a)<<endl;
        }
    }
    return 0;
}
