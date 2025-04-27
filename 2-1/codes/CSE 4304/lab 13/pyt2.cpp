#include <bits/stdc++.h>
using namespace std;

int tree[100005]; // For constructing BIT (Binary indexed tree)
int arr[100005];  // For the normal inputted values of array.

//for querying value for Binary Indexed tree
int BIT_Query(int idx)
{
    int sum=0;
    while(idx>0)
    {
        sum+=tree[idx];
        idx=idx - (idx& -idx);
    }
    return sum;
}

//for updating value of binary indexed tree
void BIT_Update(int n, int idx, int val)
{

    while(idx<=n)
    {
        tree[idx]+=val;
        idx+=(idx& (-idx));
    }
}

//for constructing the binary indexed tree
void BIT_Build(int n)
{
    for(int i=1; i<=n; i++)
    {
        BIT_Update(n, i, arr[i]);
    }

}

int main()
{
    int t, cn=0;
    cin>>t;

    while(t--)
    {
        int n, q;
        cin>>n>>q;

        tree[0]=0;

        for(int i=1; i<=n; i++)
        {
            cin>>arr[i];
            tree[i]=0;
        }

        BIT_Build(n);

        cout<<"Case "<<++cn<<":\n";

        while(q--)
        {
            int l, r, type;
            cin>>type;

            if(type==1)
            {
                cin>>l;

                // plus one is added because we are using an array indexed from one within the code.
                int val=arr[l+1];
                arr[l+1]=0;

                cout<<val<<'\n';

                BIT_Update(n, l+1, -val);
            }
            else if(type==3)
            {
                cin>>l>>r;

                // two queries are used to calculate sum within range of r to l
                int val = BIT_Query(r+1)-BIT_Query(l);
                cout<<val<<'\n';
            }
            else
            {
                int val,loc;
                cin>>loc>>val;

                arr[loc+1]=arr[loc+1]+val;
                BIT_Update(n, loc+1, val);
            }
        }

    }
    return 0;
}
