#include <iostream>

struct node
{
    node* left = NULL;
    node* right = NULL;
    int value = NULL;

};

struct tree
{
    node* root = NULL;

    void addElement(int value)
    {
        addNode(root, value);
    }

    node* addNode(node* &curr, int value)
    {
        if (curr == NULL)
        {
            node* tmp = new node;
            tmp->value = value;
            curr = tmp;
            return tmp;
        }
        if (value > curr->value)
        {
            addNode(curr->right, value);
        
        }
        if (value < curr->value)
        {
            addNode(curr->left, value);
        }   
    } 

    node* findNodeByValue(node*& curr, int value)
    {
        if (curr->value == value)
        {
            return curr;
        }
        else if (value > curr->value)
        {
            findNodeByValue(curr->right, value);

        }
        else if (value < curr->value)
        {
            findNodeByValue(curr->left, value);
        }    
    }

    node* FindParentNode(node*& curr, int value)
    {
        if (curr->left != NULL)
            if (curr->left->value == value)
                return curr;

        if (curr->right != NULL)
            if (curr->right->value == value)
                return curr;

        if (value > curr->value)
            FindParentNode(curr->right, value);

        else if (value < curr->value)
            FindParentNode(curr->left, value);
    }

    void delElement(int value)
    { 
        node* parent = FindParentNode(root,value);
        node* deleted = findNodeByValue(root, value);
        deleted = deleteNode(deleted);

        linkNode(deleted, parent, value);
    }
////////////////// не пытайся понять что тут происходит, побереги психику
    void linkNode(node*& deleted, node*& parent, int value)
    {
        if (parent->value > value && deleted == NULL)
            parent->left = NULL;

        else if (parent->value < value && deleted == NULL)
            parent->right = NULL;
        else if (deleted->left != NULL && deleted->right != NULL)
        {
            node main;
            main.value = deleted->value;
            main.right = deleted->right;
            main.left = deleted->left;
            node* tmp = findMinNode(deleted->right);
            tmp->right = main.right;
            tmp->left = main.left;

            if (parent->right->value == main.value)
                parent->right = tmp;

            else if (parent->left->value == main.value)
                parent->right = tmp;
            deleted = NULL;
        }

        else if (parent->value > deleted->value)
            parent->left = deleted;  

        else if (parent->value < deleted->value)
            parent->right = deleted;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void print_tree(node* tr, int depth)
    {
        if (tr != NULL) {
            print_tree(tr->left, depth + 1);
            for (int i = 0; i < depth; ++i) printf("   ");
            printf("%d<\n", tr->value);
            print_tree(tr->right, depth + 1);
        }
    }

    node* deleteNode(node*& curr)
    {
        if (curr->right == NULL && curr->left == NULL)
        {
            return NULL;
        }
        else if (curr->right == NULL)
        {
            return curr->left;
        }
        else if (curr->left == NULL)
        {
            return curr->right;
        }
       
    }

    node* findMinNode(node*& curr)
    {
        node* tmp;

        if (curr->left == NULL)
        {
            tmp = curr;
            curr->left = NULL;
            return tmp;
        }
        while (curr->left->left != NULL)
        {
            curr = curr->left;            
        }
        tmp = curr->left;
        curr->left = tmp->right;
        return tmp;    
    }    
};

int main()
{
    tree tree;

    tree.addElement(4);
    tree.addElement(6);
    tree.addElement(2);
    tree.addElement(10);
    tree.addElement(3);
    tree.addElement(5);
    tree.print_tree(tree.root, 1);

};

