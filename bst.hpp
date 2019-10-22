// Colton Sellers
// 20 Oct 2019

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
    friend ostream &operator<<(ostream &out, const BST &bst) {
        bst.printSideways(out, bst.Root);
        out << endl;
        bst.printVertical(out, bst.Root);
        return out;
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
    static int getHeight(const Node *n) {
        if (n == NULL)
            return 0;

        return max((getHeight(n->Left) + 1), getHeight(n->Right) + 1);

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
    static ostream &printSideways(ostream &out, const Node *curr, int level = 0) {
        const static char sp = ' ';
        const static int readabilitySpaces = 4;
        if (!curr)
            return out;
        printSideways(out, curr->Right, ++level);
        out << setfill(sp) << setw(level * readabilitySpaces) << sp;
        out << curr->Data << endl;
        printSideways(out, curr->Left, level);
        return out;
    }

    static ostream &centeredPrint(ostream &out, int space,
                                  const string &str, char fillChar = ' ') {
        auto strL = static_cast<int>(str.length());
        int extra = (space - strL) / 2;
        if (extra > 0) {
            out << setfill(fillChar) << setw(extra + strL) << str;
            out << setfill(fillChar) << setw(space - extra - strL) << fillChar;
        } else {
            out << setfill(fillChar) << setw(space) << str;
        }
        return out;
    }

    /**
     * print tree with the root at top
     *
        _____0______
     __1___      __2___
    3     4     5     6
     *
    **/
    static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                   int width, int depth, int maxDepth) {
        const static char sp = ' ';
        const static char und = '_';
        int nodes = 0;
        int maxN = pow(2, depth - 1); // NOLINT
        int SpaceForEachItem = width * pow(2, maxDepth - 1) / maxN; // NOLINT
        string bigSpace
                = string(static_cast<uint64_t>(SpaceForEachItem / 4), sp); // NOLINT
        while (nodes++ < maxN) {
            const Node *tp = q.front();
            Node *tpL = nullptr;
            Node *tpR = nullptr;
            q.pop();
            string label = "N";
            if (tp) {
                stringstream ss;
                ss << tp->Data;
                label = ss.str();
                tpL = tp->Left;
                tpR = tp->Right;
            }
            char filler = depth == maxDepth ? sp : und;
            if (depth == maxDepth) {
                centeredPrint(out, SpaceForEachItem, label, filler);
            } else {
                out << bigSpace;
                centeredPrint(out, SpaceForEachItem / 2, label, filler);
                out << bigSpace;
                q.push(tpL);
                q.push(tpR);
            }
        }
        out << endl;
        return out;
    }

    // helper function for displaying tree sideways, works recursively
    static ostream &printVertical(ostream &out, Node *curr) {
        const static int width = 6;  // must be even
        if (!curr)
            return out << "[__]";
        // figure out the maximum depth which determines how wide the tree is
        int maxDepth = getHeight(curr);
        queue<const Node *> q;
        q.push(curr);
        for (int depth = 1; depth <= maxDepth; ++depth) {
            printTreeLevel(out, q, width, depth, maxDepth);
        }
        return out;
    }

    // Recursively copies the tree
    Node *copyTree(Node *root) const {
        if (root == NULL)
            return NULL;

        Node *temp = new Node;
        temp->Data = root->Data;
        temp->Left = copyTree(root->Left);
        temp->Right = copyTree(root->Right);
        return temp;
    }

    // Recursively empties the tree
    Node *makeEmpty(Node *root) const {
        if (root == NULL)
            return NULL;
        {
            makeEmpty(root->Left);
            makeEmpty(root->Right);
            delete root;
        }
        return NULL;
    }

    // recursive helper function for counting the nodes
    int recursiveCount(Node *root) const {
        if (root == NULL)
            return 0;

        return recursiveCount(root->Left) + recursiveCount(root->Right) + 1;
    }

    // traverses the tree inOrder
    string inOrder(Node *p) const {
        string result;
        if (p != NULL) {
            if (p->Left) result += inOrder(p->Left);
            result += p->Data;
            if (p->Right) result += inOrder(p->Right);
        }
        return result;
    }

    // traverses the tree preOrder
    string preOrder(Node *p) const {
        string result;
        if (p != NULL) {
            result += p->Data;
            if (p->Left) result += preOrder(p->Left);
            if (p->Right) result += preOrder(p->Right);
        }
        return result;
    }

    // traverses the tree postOrder
    string postOrder(Node *p) const {
        string result;
        if (p != NULL) {
            if (p->Left) result += postOrder(p->Left);
            if (p->Right) result += postOrder(p->Right);
            result += p->Data;
        }
        return result;
    }

    // compare the trees and return false if they are different
    bool compare(Node *root) const {
        return recursiveCompare(Root, root);
    }

    // recursive helper for comparing all nodes
    bool recursiveCompare(Node *node1, Node *node2) const {
        bool result;

        if (node1 == NULL && node2 == NULL) return true;

        if (node2 == NULL || node1 == NULL) return false;

        if (node1->Data != node2->Data) return false;

        result = recursiveCompare(node1->Left, node2->Left)
                 && recursiveCompare(node1->Right, node2->Right);

        return result;
    }

    // read the current tree of nodes to an array
    void readToArray(Node *node, Node *array, int index) {
        if (node == NULL) return;
        readToArray(node->Left, array, index);
        array[index++] = *node;
        readToArray(node->Right, array, index);
    }

    //Recursive function to rebalance the tree
    Node *recursiveRebalance(Node *nodes, int start,
                             int end) {
        if (start > end)
            return NULL;

        //Make mid the root
        int mid = (start + end) / 2;
        Node *newNode = new Node;
        newNode->Left = NULL;
        newNode->Right = NULL;
        newNode->Data = nodes[mid].Data;


        // Construct inOrder
        newNode->Left = recursiveRebalance(nodes, start, mid - 1);
        newNode->Right = recursiveRebalance(nodes, mid + 1, end);

        return newNode;
    }

    // Recursive helper for removing a node
    Node *recursiveRemove(Node *root, T item) {
        //base case
        if (root == NULL) return root;

        // if smaller go left
        if (item < root->Data)
            root->Left = recursiveRemove(root->Left, item);

            // if greater go right
        else if (item > root->Data)
            root->Right = recursiveRemove(root->Right, item);

            // they are the same value meaning delete this one
        else {

            // if only one child on left
            if (root->Left == NULL) {
                Node *temp = root->Right;
                return temp;
            }
                // if only one child on right
            else if (root->Right == NULL) {
                Node *temp = root->Left;
                return temp;
            }

            // if two children get the smallest on right
            Node *temp = findMin(root->Right);

            // copy the new root to this node
            root->Data = temp->Data;

            // Delete its old location
            root->Right = recursiveRemove(root->Right, temp->Data);
        }
        return root;
    }

    // Used to find the smallest value in a tree
    Node *findMin(Node *root) {
        Node *current = root;

        while (current && current->Left != NULL)
            current = current->Left;

        return current;
    }

public:
    // Empty constructor
    BST() = default;

    // Construct tree with root
    explicit BST(const T &rootItem) {
        add(rootItem);
    }

    // Construct tree from array
    BST(const T arr[], int n) {
        for (int i = 0; i < n; i++) {
            add(arr[i]);
        }

        rebalance();
    }

    // Copy constructor
    BST(const BST<T> &bst) {
        Root = copyTree(bst.Root);
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
    bool add(const T &item) {

        // Create the new node
        Node *newNode = new Node;
        newNode->Left = NULL;
        newNode->Right = NULL;
        newNode->Data = item;

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
    bool remove(const T &item) {
        recursiveRemove(Root, item);
        return !contains(item);
    }

    // true if item is in BST
    bool contains(const T &item) const {

        if (isEmpty()) {
            return false;
        }

        Node *curr;
        curr = Root;

        while (curr != NULL) {
            if (curr->Data == item)
                return true;

            if (item > curr->Data)
                curr = curr->Right;
            else
                curr = curr->Left;
        }

        return false;
    }

    // inOrder traversal: Left-root-Right
    void inOrderTraverse(void visit(const T &item)) const {
        visit(inOrder(Root));
    }


    // preOrder traversal: root-Left-Right
    void preOrderTraverse(void visit(const T &item)) const {
        visit(preOrder(Root));
    }


    // postOrder traversal: Left-Right-root
    void postOrderTraverse(void visit(const T &item)) const {
        visit(postOrder(Root));
    }


    // Rebalances the tree
    void rebalance() {

        // make dynamic array that is the size of the tree
        int size = numberOfNodes();
        Node *nodes;
        nodes = new Node[size];

        // read to the array
        readToArray(Root, nodes, 0);

        // empty the old tree
        clear();

        // build the new one
        Root = recursiveRebalance(nodes, 0, size - 1);

        delete[] nodes;
    }


    // delete all nodes in tree
    void clear() {
        Root = makeEmpty(Root);
    }


    // trees are equal if they have the same structure
    // AND the same item values at all the nodes
    bool operator==(const BST<T> &other) const {
        return compare(other.Root);
    }

    // not == to each other
    bool operator!=(const BST<T> &other) const {
        return !compare(other.Root);
    }
};

#endif //BST_HPP
