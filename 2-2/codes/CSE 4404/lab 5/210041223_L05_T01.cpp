#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
#define MAX 2e18
vector <pair<ll, pair <ll,ll>>> g;
vector <ll> dist(N, MAX);
void bellmanFord(ll source, ll n)
{
    fill(dist.begin(), dist.end(), MAX);
    dist[source] = 0;

    for(ll i = 0; i < n - 1; i++)
    {
        for(auto e : g)
        {
            ll u = e.second.first;
            ll v = e.second.second;
            ll w = e.first;
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
            }
        }
    }
}
int main()
{
    ll t = 1;
    // cin >> t;
    ll n, m, q;  
    while(cin >> n >> m >> q)
    {
        if(n == 0 && m == 0 && q == 0) break;
        g.clear();
        for(ll i = 0; i < m; i++)
        {
            ll u, v, w;
            cin >> u >> v >> w;
            g.push_back({w, {u,v}});
           // g[v].push_back({w, u});
        }

        while(q--)
        {
            ll u, v;
            cin >> u >> v;
            bellmanFord(u, n);
            bool f = 0;
            for(auto e : g)
            {
                ll u = e.second.first;
                ll v = e.second.second;
                ll w = e.first;
                if(dist[v] > dist[u] + w)
                {
                   f = 1;
                }
            }
            if(dist[v] == MAX) cout << "Impossible\n";
            else if(f) cout << "-Infinity\n";
            else cout << dist[v] << endl;
        }
        cout << endl;
    }
}