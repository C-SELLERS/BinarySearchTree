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

    // refer to Data type "struct Node" as Node
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

    Node *copyTree(Node *root) const {
        if (root == NULL)
            return NULL;
        else {
            Node *temp = new Node;
            temp->Data = root->Data;
            temp->Left = copyTree(root->Left);
            temp->Right = copyTree(root->Right);
            return temp;
        }
    }

    Node *makeEmpty(Node *root) {
        if (root == NULL)
            return NULL;
        {
            makeEmpty(root->Left);
            makeEmpty(root->Right);
            delete root;
        }
        return NULL;
    }

    int recursiveCount(Node *root) const {
        if (root == NULL)
            return 0;

        return recursiveCount(root->Left) + recursiveCount(root->Right) + 1;
    }

    string inOrder(Node *p) const {
        string result;
        if (p != NULL) {
            if (p->Left) result += inOrder(p->Left);
            result += p->Data;
            if (p->Right) result += inOrder(p->Right);
        }
        return result;
    }

    string preOrder(Node *p) const {
        string result;
        if (p != NULL) {
            result += p->Data;
            if (p->Left) result += preOrder(p->Left);
            if (p->Right) result += preOrder(p->Right);
        }
        return result;
    }

    string postOrder(Node *p) const {
        string result;
        if (p != NULL) {
            if (p->Left) result += postOrder(p->Left);
            if (p->Right) result += postOrder(p->Right);
            result += p->Data;
        }
        return result;
    }

    bool compare(Node *root) const {
        return recursiveCompare(Root, root);
    }

    bool recursiveCompare(Node *node1, Node *node2) const {
        bool result;

        if (node1 == NULL && node2 == NULL)
            return true;

        //TODO: Null reference maybe a problem?
        if (node1->Data != node2->Data) {
            return false;
        }

        result = recursiveCompare(node1->Left, node2->Left)
                 && recursiveCompare(node1->Right, node2->Right);

        return result;
    }

public:
    // Empty constructor
    BST() {}

    // Construct tree with root
    //TODO: TEST IT
    explicit BST(const T &RootItem) {
        add(RootItem);
    }

    // Construct tree from array
    BST(const T Arr[], int N) {
        for (auto x : Arr) {
            add(x);
        }

        rebalance();
    }

    // Copy constructor
    BST(const BST<T> &Bst) {
        Root = copyTree(Bst.Root);
    }

    // Destructor
    virtual ~BST() {
        makeEmpty(Root);
    }

    // Returns true if no nodes in BST
    bool isEmpty() const {
        return (Root == NULL);
    }

    // Returns height of tree
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

        return true;
    }

    // Remove item, return true if successful
    //TODO: FIX OR REMAKE IT
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
                if (Item > curr->Data) {
                    curr = curr->Right;
                } else {
                    curr = curr->Left;
                }
            }
        }

        // If not found return false otherwise continue.
        if (!found) {
            return false;
        }

        // Node is a leaf node
        if (curr->Left == NULL && curr->Right == NULL) {
            if (parent->Left == curr)
                parent->Left = NULL;
            else
                parent->Right = NULL;

            delete curr;
            return true;
        }

        // Node has one child
        if ((curr->Left == NULL && curr->Right != NULL)
            || (curr->Left != NULL && curr->Right == NULL)) {

            // Child is on the Right
            if (curr->Left == NULL && curr->Right != NULL) {
                if (parent->Left == curr) {
                    parent->Left = curr->Right;
                    delete curr;
                } else {
                    parent->Right = curr->Right;
                    delete curr;
                }
            }

                // Child is on the Left
            else {
                if (parent->Left == curr) {
                    parent->Left = curr->Left;
                    delete curr;
                } else {
                    parent->Right = curr->Left;
                    delete curr;
                }
            }
            return true;
        }


        // Node has 2 children
        // We must traverse to lowest value on Right subtree
        if (curr->Left != NULL && curr->Right != NULL) {
            Node *checker;
            checker = curr->Right;

            // Right node is a leaf
            if ((checker->Left == NULL) && (checker->Right == NULL)) {
                if (parent->Left == curr) {
                    parent->Left = curr->Right;

                } else {
                    parent->Right = curr->Right;
                }

            }

                // Right node has children
            else {

                // Right subtree has Left child
                if ((curr->Right)->Left != NULL) {
                    Node *lCurr;
                    Node *lParent;
                    lParent = curr->Right;
                    lCurr = (curr->Right)->Left;

                    // Traverse to the lowest Left node
                    while (lCurr->Left != NULL) {
                        lParent = lCurr;
                        lCurr = lCurr->Left;
                    }

                    curr->Data = lCurr->Data;
                    delete lCurr;
                    lParent->Left = NULL;

                    // Right subtree does not have a Left child
                } else {
                    Node *temp;
                    temp = curr->Right;
                    curr->Data = temp->Data;
                    curr->Right = temp->Right;
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
                    curr = curr->Right;
                else
                    curr = curr->Left;
            }
        }

        return false;
    }

    // inorder traversal: Left-root-Right
    // takes a function that takes a single parameter of type T
    void inOrderTraverse(void Visit(const T &Item)) const {
        Visit(inOrder(Root));
    }


    // preorder traversal: root-Left-Right
    void preOrderTraverse(void Visit(const T &Item)) const {
        Visit(preOrder(Root));
    }


    // postorder traversal: Left-Right-root
    void postOrderTraverse(void Visit(const T &Item)) const {
        Visit(postOrder(Root));
    }


    // create dynamic array, copy all the items to the array
    // and then read the array to re-create this tree from scratch
    // so that resulting tree is balanced
    //TODO: MAKE IT
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
        return compare(Other.Root);
    }

    // not == to each other
    bool operator!=(const BST<T> &Other) const {
        return !compare(Other.Root);
    }


};
#endif  // BST_HPP
