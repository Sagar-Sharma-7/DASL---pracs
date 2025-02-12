#include <bits/stdc++.h>
using namespace std;
class TreeNode{
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int d){
        this->data=d;
        this->left=NULL;
        this->right=NULL;
    }

};
void preorder(TreeNode* root){
    if(root==NULL){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void iterative_preorder2(TreeNode* root){
    if (root == NULL)
        return;

    stack<TreeNode*> nodeStack;
    nodeStack.push(root);
    while (nodeStack.empty() == false) {
        TreeNode* node = nodeStack.top();
        cout<<node->data<<" ";
        nodeStack.pop();
        if (node->right)
            nodeStack.push(node->right);
        if (node->left)
            nodeStack.push(node->left);
    }
    cout<<endl;
}
void iterative_preorder(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* curr = root;
    while (curr != nullptr || s.empty() == false) {
        while (curr != nullptr) {
            s.push(curr);
            cout<<curr->data<<" ";
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        curr = curr->right;
    }
    cout<<endl;
}
void inorder(TreeNode* root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
void iterative_inorder(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode* curr = root;
    while (curr != nullptr || s.empty() == false) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout<<curr->data<<" ";
        curr = curr->right;
    }
    cout<<endl;
}
void postorder(TreeNode* root){
    if(root==NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
void iterative_postorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    stack<TreeNode*> stk1, stk2;
    stk1.push(root);
    TreeNode* curr;
    while (!stk1.empty()) {
        curr = stk1.top();
        stk1.pop();
        stk2.push(curr);
        if (curr->left) {
            stk1.push(curr->left);
        }
        if (curr->right) {
            stk1.push(curr->right);
        }
    }
    while (!stk2.empty()) {
        curr = stk2.top();
        stk2.pop();
        cout<<curr->data<<" ";
    }
    cout<<endl;
}
void levelorder(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            TreeNode* front=q.front();
            q.pop();
            if(front->left){
                q.push(front->left);
            }
            if(front->right){
                q.push(front->right);
            }
            cout<<front->data<<" ";
        }
        cout<<endl;
    }
}
int height(TreeNode* root){
    if(root==NULL){
        return 0;
    }
    int rightTree =1,leftTree=1;
    if(root->right){
        rightTree=1+height(root->right);
    }
    if(root->left){
        leftTree=1+height(root->left);
    }
    return max(leftTree,rightTree);
}
TreeNode* mirror(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode* newNode = new TreeNode(root->data);
    newNode->left = mirror(root->right);
    newNode->right = mirror(root->left);
    return newNode;
}
bool checkequal(TreeNode* root1,TreeNode* root2){
    if(root1==NULL&&root2==NULL){return true;}
    if (root1 == NULL || root2 == NULL || root1->data != root2->data) {
        return false;
    }
    return (checkequal(root1->left,root2->left)&&checkequal(root1->right,root2->right));
}
TreeNode* clone(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode* newNode = new TreeNode(root->data);
    newNode->left = clone(root->left);
    newNode->right = clone(root->right);
    return newNode;
}
TreeNode* createtree(){
    int value;
    cin>> value;
    if(value==-1){return NULL;}
    TreeNode* newNode=new TreeNode(value);
    cout<<"Left of Node "<<newNode->data<<": ";
    newNode->left=createtree();
    cout<<"Right of Node "<<newNode->data<<": ";
    newNode->right=createtree();
    return newNode;
}
TreeNode* insertinBST(TreeNode* node, int key) {
    if (node == NULL) 
        return new TreeNode(key);    
    if (node->data == key) 
        return node;
    if (node->data < key) 
        node->right = insertinBST(node->right, key);
    else 
        node->left = insertinBST(node->left, key);
    return node;
}
TreeNode* iterative_insertinBST(TreeNode* node, int key) {
    if (node == NULL) 
        return new TreeNode(key); 
    TreeNode* temp=node;
    TreeNode* prev=NULL;
    while(temp!=NULL){
        prev=temp;
        if (temp->data < key) 
            temp=temp->right;
        else if(temp->data>key)
            temp=temp->left;
        else {return node;}
    }   
    if (prev->data < key) 
        prev->right=new TreeNode(key);
    else 
        prev->left=new TreeNode(key);
    return node;
}
TreeNode* createBST(){
    cout<<"Enter Root Value: ";
    int val;
    cin>>val;
    TreeNode* root=new TreeNode(val);
    while (true) {
        int x;
        cout << "Enter value to be inserted in BST (-1 to stop): ";
        cin >> x;
        if (x == -1) break; 
        insertinBST(root, x);  
    }
    return root;
}
bool searchinBST(TreeNode* root,int key){
    TreeNode* temp=root;
    while(temp!=NULL){
        if(key==temp->data){return true;}
        if(key<temp->data){
            temp=temp->left;
        }
        else{
            temp=temp->right;
        }
    }
    return false;
}
TreeNode* getSuccessor(TreeNode* curr){
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}
TreeNode* deleteinBST(TreeNode* root,int x){
    if (root == nullptr)
        return root;
    if (root->data > x)
        root->left = deleteinBST(root->left, x);
    else if (root->data < x)
        root->right = deleteinBST(root->right, x);
    else {
        // when root has 0 children
        // or only right child
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        // When root has only left child
        if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // When both children are present
        TreeNode* succ = getSuccessor(root);
        root->data = succ->data;
        root->right = deleteinBST(root->right, succ->data);
    }
    return root;
}
int main(){
    bool flag=true;
    while(flag){
        cout<<"*********************** Menu ***********************" <<endl;
        cout<<"1. Create a Tree"<<endl;
        cout<<"2. Create a BST (Insert, Delete, Search)"<<endl;
        cout<<"3. Exit"<<endl<<endl;
        int op;
        cout<<"Enter option: ";
        cin>>op;
        if(op==1){
            cout<<"Enter value: ";
            TreeNode* root=createtree();
            cout<<endl;
            bool flag2=true;
            while(flag2){
                cout<<endl<<"-----------------Menu-----------------"<<endl;
                cout<<"1. Tree Traversal"<<endl;
                cout<<"2. Make a clone of tree"<<endl;
                cout<<"3. Check if two trees are equal"<<endl;
                cout<<"4. Create a mirror"<<endl;
                cout<<"5. Find the height"<<endl;
                cout<<"6. Exit"<<endl;
                int op2;
                cout<<"Enter option: ";
                cin>>op2;
                if(op2==1){
                    cout<<"Preorder: ";
                    preorder(root);
                    cout<<endl<<endl;
                    cout<<"Iterative Preorder: ";
                    iterative_preorder(root);
                    cout<<endl<<endl;
                    cout<<"Inorder: ";
                    inorder(root);
                    cout<<endl<<endl;
                    cout<<"Iterative Inorder: ";
                    iterative_inorder(root);
                    cout<<endl<<endl;
                    cout<<"Postorder: ";
                    postorder(root);
                    cout<<endl<<endl;
                    cout<<"Iterative Postorder: ";
                    iterative_postorder(root);
                    cout<<endl<<endl;
                    cout<<"Levelorder"<<endl;
                    levelorder(root);
                    cout<<endl<<endl;
                }
                else if(op2==3){
                    cout<<"Enter value of root 2: ";
                    TreeNode* root2=createtree();
                    cout<<endl;
                    if(checkequal(root,root2)){
                        cout<<"TRUE"<<endl;
                    }
                    else{
                        cout<<"FALSE"<<endl;
                    }
                }
                else if(op2==2){
                    TreeNode* root2=clone(root);
                    cout<<endl<<endl;
                    cout<<"Levelorder of Tree1:"<<endl;
                    levelorder(root);
                    cout<<endl<<endl;
                    cout<<"Levelorder of Tree2:"<<endl;
                    levelorder(root2);
                    cout<<endl<<endl;
                }
                else if(op2==4){
                    TreeNode* root2=mirror(root);
                    cout<<endl<<endl;
                    cout<<"Levelorder of Tree:"<<endl;
                    levelorder(root);
                    cout<<endl<<endl;
                    cout<<"Levelorder of mirror of Tree:"<<endl;
                    levelorder(root2);
                    cout<<endl<<endl;
                }
                else if(op2==5){
                    cout<< height(root)<<endl;
                }
                else if(op2==6){
                    flag2=false;
                }
            }
            
        }
        else if(op==2){
            TreeNode* root=createBST();
            bool flag3=true;
            cout<<endl<<endl;
            cout<<"Levelorder of Tree:"<<endl;
            levelorder(root);
            cout<<endl<<endl;
            while(flag3){
                cout<<endl<<"-----------------Menu-----------------"<<endl;
                cout<<"1. Insert node"<<endl;
                cout<<"2. Delete node"<<endl;
                cout<<"3. Search node"<<endl;
                cout<<"4. Exit"<<endl;
                int op3;
                cout<<"Enter option: ";
                cin>>op3;
                if(op3==1){
                    int key;
                    cout<<"Enter value to insert: ";
                    cin>>key;
                    TreeNode* root2=insertinBST(root,key);
                    root=root2;
                    cout<<endl<<endl;
                    cout<<"Levelorder of Tree:"<<endl;
                    levelorder(root);
                    cout<<endl<<endl;
                }
                else if(op3==2){
                    int key;
                    cout<<"Enter value to delete: ";
                    cin>>key;
                    TreeNode* root2=deleteinBST(root,key);
                    root=root2;
                    cout<<endl<<endl;
                    cout<<"Levelorder of Tree:"<<endl;
                    levelorder(root);
                    cout<<endl<<endl;
                }
                else if(op3==3){
                    int key;
                    cout<<"Enter value to search: ";
                    cin>>key;
                    if(searchinBST(root,key)){
                        cout<<"Key found"<<endl;
                    }
                    else{
                        cout<<"Key not found"<<endl;
                    }
                }
                else if(op3==4){
                    flag3=false;
                }
            }
        }
        else if(op==3){
            flag=false;
        }
    }

}
