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
    return 0;
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

public:
  // constructor, empty tree
  BST() {

  }

  // constructor, tree with root
  explicit BST(const T &RootItem) {

  }

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (i.e. rebalance)
  // Assignment specification
  // NOLINTNEXTLINE
  BST(const T Arr[], int N) {

  }

  // copy constructor
  BST(const BST<T> &Bst) {

  }

  // destructor
  virtual ~BST() {
  }

  // true if no nodes in BST
  bool isEmpty() const {
    return true;
  }

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int getHeight() const {
    return 0;
  }

  // Number of nodes in BST
  int numberOfNodes() const {
    return 0;
  }

  // add a new item, return true if successful
  bool add(const T &Item) {
    return true;
  }

  // remove item, return true if successful
  bool remove(const T &Item) {
    return true;
  }

  // true if item is in BST
  bool contains(const T &Item) const {
    return true;
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
  }

  // delete all nodes in tree
  void clear() {
  }

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BST<T> &Other) const {
    return true;
  }

  // not == to each other
  bool operator!=(const BST<T> &Other) const {
    return true;
  }
};

#endif  // BST_HPP
