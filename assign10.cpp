#include<bits/stdc++.h>
using namespace std;
#define MAX 50

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = right = NULL;
    }
};

Node* construct(int r[][MAX], int i, int j)
{
    if(!r[i][j]) return NULL;
    Node* root = new Node(r[i][j]);
    root->left = construct(r,i,r[i][j]-1);
    root->right = construct(r,r[i][j]+1,j);
    return root;
}

Node* optimalbst(int p[], int q[], int n)
{
    int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            w[i][j] = c[i][j] = r[i][j] = 0;
        }
    }
    for(int i=1;i<=n;i++){
        w[i][i] = q[i-1] + p[i] + q[i];
        c[i][i] = w[i][i];
        r[i][i] = i;
    }
    for(int sz = 2;sz<=n;++sz){
        for(int i=1;i+sz-1<=n;i++){
            int j = i+sz-1;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            c[i][j] = INT_MAX;
            for(int k=i;k<=j;k++){
                int cost = w[i][j]+c[i][k-1]+c[k+1][j];
                if(cost<c[i][j]){
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
        }
    }
    cout<<"Cost of optimal BST is: "<<c[1][n]<<endl;
    return construct(r,1,n);
}

void preorder(string words[], Node* node)
{
    if(!node) return;
    cout<<words[node->data]<<" ";
    preorder(words, node->left);
    preorder(words, node->right);
}

int main()
{
    int n;
    cout<<"How many elements do you want? ";
    cin>>n;
    string words[n+1];
    for(int i=1;i<=n;i++) cin>>words[i];
    int p[n+1];
    int q[n+1];
    cout<<"Enter values of p: \n";
    for(int i=1;i<=n;i++){
        cout<<i<<": ";
        cin>>p[i];
    }
    cout<<"Enter values of q: \n";
    for(int i=0;i<=n;i++){
        cout<<i<<": ";
        cin>>q[i];
    }
    Node* root = optimalbst(p,q,n);
    cout<<"Preorder of Optimal Binary Search Tree: "<<endl;
    preorder(words, root);
    cout<<endl;
    return 0;
}
