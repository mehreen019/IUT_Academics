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
    segment[node] = (segment[Left] ^segment[Right]);
}
ll query(ll node, ll b, ll e, ll i, ll j)
{
    if (i > e || j < b)
        return 0;
    if (b >= i && e <= j)
        return segment[node];
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e) / 2;
    ll q1=query(left, b, mid, i,j);
    ll q2=query(right, mid + 1, e, i,j);
    return q1^q2;
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
        cin>>a>>b;
        cout<<query(1,1,n,a,b)<<endl;
    }
    return 0;
}
