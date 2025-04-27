#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dll long double
#define dl double
#define ull unsigned long long
#define pb push_back
#define all(s) s.begin(), s.end()
#define bug(x) cout << #x << " = " << x << endl;
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL);
#define ff first
#define ss second
#define nl '\n'

const ll MAX = 2e15 + 5;
const ll N = 2e6 + 5;

ll tree[N * 3] = {0};
ll lazy[N * 3] = {0};
ll input[N] = {0};

void init(ll node, ll b, ll e)
{
    if(b == e)
    {
        tree[node] = input[b];
        return;
    }
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e)/2;

    init(left, b, mid);
    init(right, mid + 1, e);

    tree[node] = tree[left] ^ tree[right];
}

ll query(ll node, ll b, ll e, ll i, ll j)
{
    if(i > e || j < b) // no overlap at all
        return 0;
    if( b >= i && e <= j) // complete overlap
        return tree[node];

    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e)/2;

    ll q1 = query(left, b, mid, i, j);
    ll q2 = query(right, mid + 1, e, i, j);
    return q1 ^ q2;
}

void update(ll node, ll b, ll e, ll i, ll x)
{
    if(i > e || i < b)
    {
        return;
    }
    if(b >= i && e <= i)
    {
        tree[node] += x;
        return;
    }
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e)/2;

    update(left, b, mid, i, x);
    update(right, mid + 1, e, i, x);

    tree[node] = tree[left] + tree[right];
}
void lazy_update(ll node, ll b, ll e, ll i, ll j, ll x)
{
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e)/2;

    if(lazy[node] != 0)
    {
        tree[node] += (e - b + 1) * lazy[node];
        if(b != e)
        {
            lazy[left] += lazy[node];
            lazy[right] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(b > e || i > e || j < b)
    {
        return;
    }
    if(b >= i && e <= j)
    {
        tree[node] += (e - b + 1) * x;
        if(b != e)
        {
            lazy[left] += x;
            lazy[right] += x;
        }
        return;
    }

    lazy_update(left, b, mid, i, j, x);
    lazy_update(right, mid + 1, e, i,j, x);

    tree[node] = tree[left] + tree[right];

}
ll lazy_query(ll node, ll b, ll e, ll i, ll j)
{
    ll left = node * 2;
    ll right = node * 2 + 1;
    ll mid = (b + e)/2;
    if(lazy[node] != 0)
    {
        tree[node] += (e - b + 1) * lazy[node];
        if(b != e)
        {
            lazy[left] += lazy[node];
            lazy[right] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(i > e || j < b)
    {
        return 0;
    }
    if(b >= i && e <= j)
    {
        return tree[node];
    }

    ll q1 = lazy_query(left, b, mid, i, j);
    ll q2 = lazy_query(right, mid + 1, e, i, j);

    return q1 + q2;
}
int main()
{
    ll n, q;
    cin >> n >> q;
    for(ll i = 1; i <= n; i++)
    {
        cin >> input[i];
    }
    init(1,1,n);

    while(q--)
    {
        ll op, k, a, b, u;
        cin >> op;
        if(op == 1)
        {
            cin >> a >> b >> u;
            lazy_update(1,1,n,a,b,u);
        }
        else if(op == 2)
        {
            cin >> k;
            cout << lazy_query(1, 1, n, k, k) << endl;
        }
    }

    return 0;
}
