#include <iostream>
#define maxx 200009
#define ll long long
using namespace std;

const int MAX  = (1e9 + 10);
int arr[maxx];
int segment[maxx * 3];
void init(int node, int b, int e)
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
    segment[node] = max(segment[Left] ,segment[Right]);
}

int Find(int node, int b, int e, int x, int ans){
    if(segment[node]<x) return 0;
    if(b==e) return b;

    int cur;
    //cout<<cur<<" ";
    int left = node * 2;
    int right = node * 2 + 1;
    int mid=(b+e)/2;
    if(x<=segment[left]){
        cur=Find(left, b, mid, x, ans);
        ans=max(ans, cur);
    }
    else if(x<=segment[right]){
        cur=Find(right, mid+1,e, x, ans);
        ans=max(ans, cur);
    }
    return ans;
}

void update(int node, int b, int e, int i, int newvalue)
{
    if (i > e || i < b)
        return;
    if (b >= i && e <= i) {
        segment[node] = newvalue;
        return;
    }
    int Left = node * 2;
    int Right = node * 2 + 1;
    int mid = (b + e) / 2;
    update(Left, b, mid, i, newvalue);
    update(Right, mid + 1, e, i, newvalue);
    segment[node] = max(segment[Left] , segment[Right]);
}
int main()
{

    int n, q,x,a,b;
    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> arr[i];
    for(int i = 1; i <= maxx*3; i++){
        segment[i]=-MAX;
    }
    init(1, 1, n);
    while(q--)
    {
        cin>>x;
        int idx=Find(1,1,n,x,0),ans=0;
        update(1,1,n,idx,arr[idx]-x);
        cout<<idx<<" ";
        arr[idx]-=x;
    }
    return 0;
}
