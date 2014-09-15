#include <stdio.h>
#include <stdlib.h>

#define TEST_SIZE 10
#define TEST_SPACE 50

/**
 * The segmentation was caused because the root node of the binary tree was
 * never declared. The memory leak occurred because none of the nodes were
 * ever freed. Fix these by initializing a root node and freeing all the
 * nodes in the tree's destructor.
 */

struct Node
{
    int value;
    Node * left;
    Node * right;
    Node(int v)
    {
        value = v;
        left = NULL;
        right = NULL;
    }

    /** @brief Inserts an integer into the subtree rooted at this node.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    bool insert(int val)
    {
        if(val == value)
        {
            return false;
        }
        else if(val < value)
        {
            if(left == NULL)
            {
                left = new Node(val);
                return true;
            }
            else
            {
                return left->insert(val);
            }
        }
        else
        {
            if(right == NULL)
            {
                right = new Node(val);
                return true;
            }
            else
            {
                return right->insert(val);
            }
        }
    }

    /** @brief Finds an integer in the subtree rooted at this node.

    @return whether or not the entry exists in this subtree.

    */
    bool find(int val)
    {
        if(val == value)
        {
            return true;
        }
        else if(val < value)
        {
            if(left == NULL)
            {
                left = new Node(val);
                return false;
            }
            else
            {
                return left->find(val);
            }
        }
        else
        {
            if(right == NULL)
            {
                return false;
            }
            else
            {
                return right->find(val);
            }
        }
    }
};

class BinarySearchTree
{
private:
    Node * root;
public:
    BinarySearchTree(int val)
    {
        root = new Node(val);
    }

    ~BinarySearchTree()
    {
        deletePostorder(root);
    }

    void deletePostorder(Node * root)
    {
        if (root != NULL)
        {
            deletePostorder(root->left);
            deletePostorder(root->right);
            delete root;
        }
    }

    /** @brief Inserts an integer into this tree.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    bool insert(int val)
    {
        return root->insert(val);
    }

     /** @brief Finds an integer in this tree.

    @return whether or not the entry exists in this tree.

    */
    bool find(int val)
    {
        return root->find(val);
    }
};

int main(int argc, char ** argv)
{
    BinarySearchTree b(4);
    srand(42);

    // first insert some test numbers
    printf("\n\nadding %d numbers\n\n", TEST_SIZE);
    for(int i = 0; i < TEST_SIZE; i++)
    {
        int k = rand() % TEST_SPACE;
        printf("Inserting %d... ", k);
        bool s = b.insert(k);
        if(s)
        {
            printf("OK\n");
        }
        else
        {
            printf("already in\n");
        }
    }

    // now print out all the numbers in the tree
    // (by finding all possible numbers, not by traversing the tree)
    printf("\n\nok, now printing contents (the slow way)\n\n");
    for(int j = 0; j < TEST_SPACE; j++)
    {
        if(b.find(j))
        {
            printf("%d ", j);
        }
    }

    printf("\n\nall done\n\n");
    return 0;
}
