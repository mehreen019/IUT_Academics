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
#define N 20000
#define MAX 2e18

ll parent[N];
ll set_size[N];

void make_sets(ll v)
{
    parent[v] = v;
    set_size[v] = 1;
}
ll find_set(ll v)
{
    if(v == parent[v]) return v;
    else 
    {
        parent[v] = find_set(parent[v]);
        return parent[v];
    }
}
void union_sets(ll a, ll b)
{
    a = find_set(a);
    b = find_set(b);

    if(a != b)
    {
        if(set_size[b] > set_size[a]) swap(a, b);
        parent[b] = a;
        set_size[a] += set_size[b];
    }
}

int main(int argc, char const *argv[])
{
    fastio
    ll t = 1, caseno = 0;
  //  cin >> t;
    while(t--)
    {
        ll n, m;
        cin >> n >> m;
        vector < pair <ll, pair <ll, ll>>> g;
        for(ll i = 1; i <= n; i++) make_sets(i);
        for(ll i = 1; i <= m; i++)
        {
            ll w, u, v;
            cin >> w >> u >> v;
            g.push_back({w, {u, v}});
        } 
        sort(all(g));
        ll cost = 0;

        for(auto e : g)
        {
            ll u = e.second.first;
            ll v = e.second.second;
            ll w = e.first;

            if(find_set(u) != find_set(v))
            {
                cost += w;
                union_sets(u, v);
            }
        } 
        cout << cost << endl;

    }
    
    return 0;
}