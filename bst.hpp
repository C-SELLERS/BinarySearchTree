// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the Data
// Uses templates to store any type of Data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class BST {
    // display BST tree in a human-readable format
    friend ostream &operator<<(ostream &Out, const BST &Bst) {
        Bst.printSideways(Out, Bst.Root);
        Out << endl;
        Bst.printVertical(Out, Bst.Root);
        return Out;
    }

private:
    // Node for BST
    struct Node {
        T Data;
        struct Node *Left;
        struct Node *Right;
    };

    // refer to data type "struct Node" as Node
    using Node = struct Node;

    // root of the tree
    Node *Root{nullptr};

    // height of a Node, nullptr is 0, Root is 1, static, no access to 'this'
    static int getHeight(const Node *N) {
        if (N == NULL)
            return 0;
        else {
            return max((getHeight(N->Left)+1), getHeight(N->Right)+1);
        }
    }

    /**
     * print tree sideways with root on left
                  6
              2
                  5
          0
                  4
              1
                  3
     */
    static ostream &printSideways(ostream &Out, const Node *Curr, int Level = 0) {
        const static char SP = ' ';
        const static int ReadabilitySpaces = 4;
        if (!Curr)
            return Out;
        printSideways(Out, Curr->Right, ++Level);
        Out << setfill(SP) << setw(Level * ReadabilitySpaces) << SP;
        Out << Curr->Data << endl;
        printSideways(Out, Curr->Left, Level);
        return Out;
    }

    static ostream &centeredPrint(ostream &Out, int Space,
                                  const string &Str, char FillChar = ' ') {
        auto StrL = static_cast<int>(Str.length());
        int Extra = (Space - StrL) / 2;
        if (Extra > 0) {
            Out << setfill(FillChar) << setw(Extra + StrL) << Str;
            Out << setfill(FillChar) << setw(Space - Extra - StrL) << FillChar;
        } else {
            Out << setfill(FillChar) << setw(Space) << Str;
        }
        return Out;
    }

    /**
     * print tree with the root at top
     *
        _____0______
     __1___      __2___
    3     4     5     6
     *
    **/
    static ostream &printTreeLevel(ostream &Out, queue<const Node *> &Q,
                                   int Width, int Depth, int MaxDepth) {
        const static char SP = ' ';
        const static char UND = '_';
        int Nodes = 0;
        int MaxN = pow(2, Depth - 1);
        int SpaceForEachItem = Width * pow(2, MaxDepth - 1) / MaxN; // NOLINT
        string
                Bigspace = string(static_cast<uint64_t>(SpaceForEachItem / 4), SP);
        while (Nodes++ < MaxN) {
            const Node *Tp = Q.front();
            Node *TpL = nullptr;
            Node *TpR = nullptr;
            Q.pop();
            string Label = "N";
            if (Tp) {
                stringstream Ss;
                Ss << Tp->Data;
                Label = Ss.str();
                TpL = Tp->Left;
                TpR = Tp->Right;
            }
            char Filler = Depth == MaxDepth ? SP : UND;
            if (Depth == MaxDepth) {
                centeredPrint(Out, SpaceForEachItem, Label, Filler);
            } else {
                Out << Bigspace;
                centeredPrint(Out, SpaceForEachItem / 2, Label, Filler);
                Out << Bigspace;
                Q.push(TpL);
                Q.push(TpR);
            }
        }
        Out << endl;
        return Out;
    }

    // helper function for displaying tree sideways, works recursively
    static ostream &printVertical(ostream &Out, Node *Curr) {
        const static int WIDTH = 6;  // must be even
        if (!Curr)
            return Out << "[__]";
        // figure out the maximum depth which determines how wide the tree is
        int MaxDepth = getHeight(Curr);
        queue<const Node *> Q;
        Q.push(Curr);
        for (int Depth = 1; Depth <= MaxDepth; ++Depth) {
            printTreeLevel(Out, Q, WIDTH, Depth, MaxDepth);
        }
        return Out;
    }

    Node *copyTree(Node *root) {
        if (root == NULL)
            return NULL;
        else {
            Node *temp = new Node;
            temp->Data = root->Data;
            temp->Left = copyInOrder(root->Left);
            temp->Right = copyInOrder(root->Right);
            return temp;
        }
    }

    Node *makeEmpty(Node *root) {
        if (root == NULL)
            return NULL;
        {
            makeEmpty(root->left);
            makeEmpty(root->right);
            delete root;
        }

    }

    int recursiveCount (Node *root) {
        if (root == NULL)
            return 0;

        return recursiveCount(root->Left) + recursiveCount(root->Right) + 1;
    }


public:
    // Empty constructor
    BST() {
    }

    // Constructor, tree with root
    explicit BST(const T &RootItem) {
        Root = new Node;
        Root->Data = *RootItem;

    }

    // given an array of length n
    // create a tree to have all items in that array
    // with the minimum height (i.e. rebalance)
    BST(const T Arr[], int N) {

    }

    // copy constructor
    BST(const BST<T> &Bst) {
        Root = copyTree(*Bst);
    }

    // destructor
    virtual ~BST() {
        MakeEmpty(Root);
    }

    // true if no nodes in BST
    bool isEmpty() const {
        return (Root);
    }

    // 0 if empty, 1 if only root, otherwise
    // height of root is max height of subtrees + 1
    int getHeight() const {
        return getHeight(Root);
    }

    // Number of nodes in BST
    int numberOfNodes() const {
        return recursiveCount(Root);
    }

    // Add a new item, return true if successful
    bool add(const T &Item) {

        // Create the new node
        Node *newNode = new Node;
        newNode->Left = NULL;
        newNode->Right = NULL;
        newNode->Data = Item;

        // Pointers for current and parent
        Node *current;
        Node *parent = NULL;
        current = Root;

        // If the root is null make the new node the root
        if (current == NULL) {
            Root = newNode;
            return true;
        }

        // Find the appropriate parent
        while (current != NULL) {
            parent = current;
            if (newNode->Data > current->Data)
                current = current->Right;
            else
                current = current->Left;
        }

        // Place it in the appropriate leaf spot
        if (newNode->Data < parent->Data)
            parent->Left = newNode;
        else
            parent->Right = newNode;

    }

    // Remove item, return true if successful
    bool remove(const T &Item) {

        if (isEmpty()) {
            return false;
        }

        bool found = false;
        Node *curr;
        Node *parent = NULL;
        curr = Root;

        // Find the item and keep track of the parent
        while (curr != NULL) {
            if (curr->Data == Item) {
                found = true;
                break;
            } else {
                parent = curr;
                if (Item > curr->Data)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
        }

        // If not found return false otherwise continue.
        if (!found) {
            return false;
        }

        // Node is a leaf node
        if (curr->left == NULL && curr->right == NULL) {
            delete curr;
            return true;
        }

        // Node has one child
        if ((curr->left == NULL && curr->right != NULL)
            || (curr->left != NULL && curr->right == NULL)) {

            // Child is on the right
            if (curr->left == NULL && curr->right != NULL) {
                if (parent->left == curr) {
                    parent->left = curr->right;
                    delete curr;
                } else {
                    parent->right = curr->right;
                    delete curr;
                }
            }

                // Child is on the left
            else {
                if (parent->left == curr) {
                    parent->left = curr->left;
                    delete curr;
                } else {
                    parent->right = curr->left;
                    delete curr;
                }
            }
            return true;
        }


        // Node has 2 children
        // We must traverse to lowest value on right subtree
        if (curr->Left != NULL && curr->Right != NULL) {
            Node *checker;
            checker = curr->Right;

            // Right node is a leaf
            if ((checker->Left == NULL) && (checker->Right == NULL)) {
                curr = checker;
                delete checker;
                curr->right = NULL;
            }

                // Right node has children
            else {

                // Right subtree has left child
                if ((curr->Right)->Left != NULL) {
                    Node *lCurr;
                    Node *lParent;
                    lParent = curr->Right;
                    lCurr = (curr->Right)->Left;

                    // Traverse to the lowest left node
                    while (lCurr->Left != NULL) {
                        lParent = lCurr;
                        lCurr = lCurr->left;
                    }

                    curr->Data = lCurr->Data;
                    delete lCurr;
                    lParent->left = NULL;

                    // Right subtree does not have a left child
                } else {
                    Node *temp;
                    temp = curr->right;
                    curr->data = temp->data;
                    curr->right = temp->right;
                    delete temp;
                }

            }
            return true;
        }

        return false;
    }

    // true if item is in BST
    bool contains(const T &Item) const {

        if (isEmpty()) {
            return false;
        }

        Node *curr;
        curr = Root;

        while (curr != NULL) {
            if (curr->Data == Item) {
                return true;
            } else {
                if (Item > curr->Data)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
        }

        return false;
    }

    // inorder traversal: left-root-right
    // takes a function that takes a single parameter of type T
    void inOrderTraverse(void Visit(const T &Item)) const {

    }

    // preorder traversal: root-left-right
    void preOrderTraverse(void Visit(const T &Item)) const {

    }

    // postorder traversal: left-right-root
    void postOrderTraverse(void Visit(const T &Item)) const {

    }

    // create dynamic array, copy all the items to the array
    // and then read the array to re-create this tree from scratch
    // so that resulting tree is balanced
    void rebalance() {
        //Get size of tree
        //Create array of that size
        //Copy all items to that array
        //Balance it (Private method?)

    }

    // delete all nodes in tree
    void clear() {
        Root = makeEmpty(Root);
    }


    // trees are equal if they have the same structure
    // AND the same item values at all the nodes
    bool operator==(const BST<T> &Other) const {
        //Recursive comparison?
        return true;
    }

    // not == to each other
    bool operator!=(const BST<T> &Other) const {
        //Same as above but the opposite.
        return true;
    }
};
#endif  // BST_HPP
