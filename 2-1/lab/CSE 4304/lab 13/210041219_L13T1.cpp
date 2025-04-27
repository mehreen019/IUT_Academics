#include <iostream>
#define maxx 200005
using namespace std;

const int MAX  = 1e9 + 10;
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
    segment[node] = min(segment[Left] ,segment[Right]);
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
    return min(query(left, b, mid, i, j), query(right, mid + 1, e, i, j));
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
    segment[node] = min(segment[Left] , segment[Right]);
}
int main()
{

    int n, q,x,a,b;
    cin >> n >> q;;
    for(int i = 1; i <= n; i++) cin >> arr[i];
    init(1, 1, n);

    while(q--)
    {
        cin>>x;
        if(x==1)
        {
            cin>>a>>b;
            update(1, 1, n, a, b);
            /*for(int i=0;i<n*3;i++){
                cout<<segment[i]<<" ";
            }*/
        }
        else{
                cin>>a>>b;
            cout<<query(1, 1, n, a, b)<<endl;}
        }
    return 0;
}
