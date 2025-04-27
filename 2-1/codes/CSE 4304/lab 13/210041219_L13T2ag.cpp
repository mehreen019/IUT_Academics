#include <iostream>
#define maxx 200010
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
int query(int node, int b, int e, int i, int j)
{
    if (i > e || j < b)
        return MAX;
    if (b >= i && e <= j)
        return segment[node];
    int left = node * 2;
    int right = node * 2 + 1;
    int mid = (b + e) / 2;
    return max(query(left, b, mid, i, j), query(right, mid + 1, e, i, j));
}

int Find(int x, int node){
    if(segment[node]<x) return MAX;

    int cur=segment[node];
    //cout<<cur<<" ";
    int left = node * 2;
    int right = node * 2 + 1;
    if(x<=segment[left]){
        cur=min(cur, Find(x, left));
    }
    else if(x<=segment[right]){
        cur=min(cur, Find(x, right));
    }
    return cur;
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
    cin >> n >> q;;
    for(int i = 1; i <= n; i++) cin >> arr[i];
    for(int i = 1; i <= maxx*3; i++){
        segment[i]=-MAX;
    }
    init(1, 1, n);
    while(q--)
    {
        cin>>x;
        int idx=Find(x,1),ans=0;
        if(idx!=MAX){
            //cout<<"ok";
            for(int i=1;i<=n;i++){
                if(arr[i]==idx){
                    ans=i;
                    arr[i]=idx-x;
                    break;
                }
            }
            update(1,1,n,ans,idx-x);
        }
        cout<<ans<<" ";
    }
    return 0;
}
