#include <bits/stdc++.h>
using namespace std;

// A utility function to get the middle index from corner indexes.
int getMid(int s, int e) { return (s + e)/2; }

/* A recursive function to get the sum of values in the given range
    of the array. The following are parameters for this function.

    st --> Pointer to segment tree
    si --> Index of current node in the segment tree. Initially
            0 is passed as root is always at index 0
    ss & se --> Starting and ending indexes of the segment represented
                by current node, i.e., st[si]
    qs & qe --> Starting and ending indexes of query range */
int getSumUtil(int *st, int ss, int se, int qs, int qe, int si)
{
    // If segment of this node is a part of given range, then return
    // the sum of the segment
    if (qs <= ss && qe >= se)
        return st[si];

    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return 0;

    // If a part of this segment overlaps with the given range
    int mid = getMid(ss, se);
    return getSumUtil(st, ss, mid, qs, qe, 2*si+1) +
        getSumUtil(st, mid+1, se, qs, qe, 2*si+2);
}

/* A recursive function to update the nodes which have the given
index in their range. The following are parameters
    st, si, ss and se are same as getSumUtil()
    i --> index of the element to be updated. This index is
            in the input array.
diff --> Value to be added to all nodes which have i in range */
int updateValueUtil(int arr[], int *st, int b, int e, int i, int node)
{
    // Base Case: If the input index lies outside the range of
    // this segment
    if (i < b || i > e)
        return INT_MAX;
    if (b == e)
    {
        st[node] = arr[b];
        return arr[b];
    }
    // If the input index is in range of this node, then update
    // the value of the node and its children
    if (b != e)
    {
        int mid = getMid(b, e);
            st[node] = min(updateValueUtil(arr, st, b, mid, i, node*2),
                           updateValueUtil(arr, st, mid+1, e, i, node*2+1));
            return st[node];
    }
}

// The function to update a value in input array and segment tree.
// It uses updateValueUtil() to update the value in segment tree
void updateValue(int arr[], int *st, int n, int i, int new_val)
{
    // Check for erroneous input index
    if (i < 0 || i > n-1)
    {
        cout<<"Invalid Input";
        return;
    }

    // Get the difference between new value and old value
    int diff = new_val - arr[i];

    // Update the value in array
    arr[i] = new_val;

    // Update the values of nodes in segment tree
    updateValueUtil(arr, st, 1, n, i, 1);
}

// Return sum of elements in range from index qs (query start)
// to qe (query end). It mainly uses getSumUtil()
int getSum(int *st, int n, int qs, int qe)
{
    // Check for erroneous input values
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        cout<<"Invalid Input";
        return -1;
    }

    return getSumUtil(st, 0, n-1, qs, qe, 0);
}

// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
    // If there is one element in array, store it in current node of
    // segment tree and return
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }

    // If there are more than one elements, then recur for left and
    // right subtrees and store the sum of values in this node
    int mid = getMid(ss, se);
    st[si] = min(constructSTUtil(arr, ss, mid, st, si*2),
            constructSTUtil(arr, mid+1, se, st, si*2+1));
    return st[si];
}

/* Function to construct segment tree from given array. This function
allocates memory for segment tree and calls constructSTUtil() to
fill the allocated memory */
int *constructST(int arr[], int n)
{
    // Allocate memory for the segment tree

    //Height of segment tree
    int x = (int)(ceil(log2(n)));

    //Maximum size of segment tree
    int max_size = 2*(int)pow(2, x) - 1;

    // Allocate memory
    int *st = new int[max_size+1];

    // Fill the allocated memory st
    constructSTUtil(arr, 1, n, st, 1);

    // Return the constructed segment tree
    return st;
}

// Driver program to test above functions
int main()
{
    int n,q,x,a,b;
    cin>>n>>q;
    int arr[n];
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int *st = constructST(arr, n);


    while(q--){
        cin>>x;
        if(x==1){
            cin>>a>>b;
            updateValue(arr, st, n, a-1, b);
        }
    }

    for(int i=0;i<16;i++){
        cout<<st[i]<<" ";
    }
    //cout<<"Sum of values in given range = "<<getSum(st, n, 1, 3)<<endl;

    // Update: set arr[1] = 10 and update corresponding
    // segment tree nodes
    //updateValue(arr, st, n, 1, 10);

    // Find sum after the value is updated
    //cout<<"Updated sum of values in given range = "
            //<<getSum(st, n, 1, 3)<<endl;
    return 0;
}
