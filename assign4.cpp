#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int val;
    node *left;
    node *right;
    bool lf, rf;
    node()
    {
        left = NULL;
        right = NULL;
        lf = rf = true;
    }
    node(int x)
    {
        val = x;
        left = NULL;
        right = NULL;
        lf = rf = true;
    }
};

void inorder(node *root, vector<node *> &v)
{
    if (root == NULL)
        return;
    inorder(root->left, v);
    v.push_back(root);
    // cout<<root->val;
    inorder(root->right, v);
}

void insertIntoTBST(node *&root, int key)
{
    node *nw = new node(key);
    if (root->left == NULL)
    {
        root->left = nw;
        nw->left = root;
        nw->right = root;
        return;
    }
    node *temp = root->left;
    while (true)
    {
        if (temp->val > key)
        {
            if (temp->lf)
            {
                nw->left = temp->left;
                temp->left = nw;
                temp->lf = false;
                nw->right = temp;
                return;
            }
            else
                temp = temp->left;
        }
        else
        {
            if (temp->rf)
            {
                nw->right = temp->right;
                temp->right = nw;
                temp->rf = false;
                nw->left = temp;
                return;
            }
            else
                temp = temp->right;
        }
    }
}

node *leftMost(node *n, node *dm)
{
    if (n == NULL)
        return NULL;

    while (!n->lf && n->left != dm)
        n = n->left;

    return n;
}

void inorder_TBST(node *root)
{
    node *dm = root;
    node *cur = leftMost(root->left, dm);
    cout << "Inoder traversal of threaded binary tree :" << endl;
    while (cur != dm)
    {
        cout << cur->val << " ";
        if (cur->rf)
            cur = cur->right;
        else
            cur = leftMost(cur->right, dm);
    }
}

void insertIntoBST(node *&root, int key)
{
    node *nw = new node(key);
    if (root == NULL)
    {
        root = nw;
        return;
    }
    node *temp = root;
    while (true)
    {
        if (temp->val > key)
        {
            if (temp->left == NULL)
            {
                temp->left = nw;
                return;
            }
            else
                temp = temp->left;
        }
        else
        {
            if (temp->right == NULL)
            {
                temp->right = nw;
                return;
            }
            else
                temp = temp->right;
        }
    }
}

node *convertToTBST(node *&root, vector<node *> inord)
{
    node *dummy = new node(1000);
    dummy->left = root;
    dummy->right = dummy;
    dummy->lf = false;
    int i = 0;

    while (i < inord.size())
    {
        if (inord[i]->left == NULL)
        {
            if (i != 0)
                inord[i]->left = inord[i - 1];
            else
                inord[i]->left = dummy;
        }
        else
            inord[i]->lf = false;
        if (inord[i]->right == NULL)
        {
            if (i != inord.size() - 1)
                inord[i]->right = inord[i + 1];
            else
                inord[i]->right = dummy;
        }
        else
            inord[i]->rf = false;
        i++;
    }
    return dummy;
}

int main()
{
    // node *tbst = new node(999);
    // insertIntoTBST(tbst, 10);
    // insertIntoTBST(tbst, 7);
    // insertIntoTBST(tbst, 9);
    // insertIntoTBST(tbst, 8);
    // insertIntoTBST(tbst, 12);

    // vector<int> ans = inorder_TBST(tbst);
    // cout << "Inorder traversal of threaded binary tree : " << endl;
    // for (auto it : ans)
    //     cout << it << " ";
    // cout << endl;
    
    while(true)
    {
       cout<<"";
       break;
    }

    node *bst1 = NULL;
    insertIntoBST(bst1, 10);
    insertIntoBST(bst1, 8); // complete tree
    insertIntoBST(bst1, 12);
    insertIntoBST(bst1, 9);
    insertIntoBST(bst1, 7);
    insertIntoBST(bst1, 11);
    insertIntoBST(bst1, 15);

    vector<node *> inord1;
    inorder(bst1, inord1);
    node *newRoot1 = convertToTBST(bst1, inord1);
    inorder_TBST(newRoot1);
    cout << endl;

    bst1 = NULL;
    insertIntoBST(bst1, 10);
    insertIntoBST(bst1, 9); // left skew tree
    insertIntoBST(bst1, 8);
    insertIntoBST(bst1, 7);
    insertIntoBST(bst1, 6);

    inorder(bst1, inord1);
    newRoot1 = convertToTBST(bst1, inord1);
    inorder_TBST(newRoot1);
    cout << endl;

    bst1 = NULL;
    insertIntoBST(bst1, 1);
    insertIntoBST(bst1, 2); // right skew tree
    insertIntoBST(bst1, 3);
    insertIntoBST(bst1, 4);
    insertIntoBST(bst1, 5);

    inorder(bst1, inord1);
    newRoot1 = convertToTBST(bst1, inord1);
    inorder_TBST(newRoot1);
    cout << endl;

    bst1 = NULL;
    insertIntoBST(bst1, 10);
    insertIntoBST(bst1, 20); // zig-zag tree
    insertIntoBST(bst1, 15);
    insertIntoBST(bst1, 18);
    insertIntoBST(bst1, 16);

    inorder(bst1, inord1);
    newRoot1 = convertToTBST(bst1, inord1);
    inorder_TBST(newRoot1);
    cout << endl;
}
