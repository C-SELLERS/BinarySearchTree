/**
 * Testing BST - Binary Search Tree functions
 *
 * This file has series of tests for BST
 * Each test is independent and uses assert statements
 * Test functions are of the form
 *
 *      test_netidXX()
 *
 * where netid is UW netid and XX is the test number starting from 01
 *
 * Test functions can only use the public functions from BST
 * testBSTAll() is called from main in main.cpp
 * testBSTAll calls all other functions
 * @author Multiple
 * @date ongoing
 */

#include "bst.hpp"
#include <cassert>


using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor {
public:
  // never create an instance of TreeVisitor object
  // we'll just use the static functions
  TreeVisitor() = delete;

  // insert output to SS rather than cout, so we can test it
  static stringstream SS;

  static string getSS() {
    return SS.str();
  }

  static void resetSS() {
    SS.str(string());
  }
  // instead of cout, insert item into a string stream
  static void visitor(const string &Item) {
    SS << Item;
  }

  // instead of cout, insert item into a string stream
  static void visitor(const int &Item) {
    SS << Item;
  }
};

// initialize the static variable
//  warning: initialization of 'SS' with static storage duration
//  may throw an exception that cannot be caught [cert-err58-cpp]
//  Not sure how to do it without making code harder to read
//  NOLINTNEXTLINE
stringstream TreeVisitor::SS;

/**
 * Test functions by Yusuf Pisan
 */

// Testing ==
void testPisan01() {
  cout << "Starting testPisan01" << endl;
  cout << "* Testing == and !=" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  // == and != for empty trees
  assert(B1 == B2 && (!(B1 != B2)));
  B1.add("c");
  B2.add("c");
  B3.add("b");
  // == and !- for 1-Node trees B1, B2, B3
  assert(B1 == B2 && (!(B1 != B2)));
  assert(B1 != B3 && (!(B1 == B3)));
  cout << "Ending testPisan01" << endl;
}

// Testing == in detail
void testPisan02() {
  cout << "Starting testPisan02" << endl;
  cout << "* Testing == and != with more detail" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  // == for 5-Node trees B1, B2
  assert(B1 == B2 && (!(B1 != B2)));

  BST<string> B4(B3);
  // copy constructor for 1-Node trees B3, B4
  assert(B3 == B4 && (!(B3 != B4)));

  BST<string> B5(B1);
  // copy constructor for 5-Node trees B1, B5
  assert(B1 == B5 && (!(B5 != B1)));

  BST<string> B7("b");
  // 1-param constructor for 1-Node trees B3, B7
  assert(B3 == B7 && (!(B3 != B7)));

  cout << "Ending testPisan02" << endl;
}

// Testing traversal
void testPisan03() {
  cout << "Starting testPisan03" << endl;
  cout << "* Testing traversal" << endl;
  BST<string> B1;
  BST<string> B2;
  BST<string> B3;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
    B2.add(S);

  B3.add("b");

  TreeVisitor::resetSS();
  B1.inOrderTraverse(TreeVisitor::visitor);
  string Result = "acfgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.preOrderTraverse(TreeVisitor::visitor);
  Result = "cafgx";
  assert(TreeVisitor::getSS() == Result);

  TreeVisitor::resetSS();
  B1.postOrderTraverse(TreeVisitor::visitor);
  Result = "axgfc";
  assert(TreeVisitor::getSS() == Result);

  cout << "Visual check B1:" << endl;
  cout << B1 << endl;
  cout << "Ending testPisan03" << endl;
}

/**
 * Test functions by Sample Sample
 */

// Testing samplefunctionality
void testSample01() {
  cout << "Starting testSample01" << endl;
  BST<string> B1;
  BST<string> B2;
  for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
    B1.add(S);

  cout << "Tree 1" << endl;
  cout << B1 << endl;

  cout << "Height Test" << endl;
  int height = B1.getHeight();
  assert(height == 4);
  cout << "Height Success" << endl;

  cout << "Number of Nodes" << endl;
  int nodes = B1.numberOfNodes();
  assert(nodes == 5);
  cout << "Number of Nodes Success" << endl;

  cout << "Clear Test" << endl;
  B1.clear();
  cout << B1 << endl;
  cout << "Clear Success" << endl;

  cout << "Height Test" << endl;
  height = B1.getHeight();
  assert(height == 0);
  cout << "Height Success" << endl;

  cout << "Number of Nodes" << endl;
  nodes = B1.numberOfNodes();
  assert(nodes == 0);
  cout << "Number of Nodes Success" << endl;


  for (auto &S : vector<string>{"c", "f", "a", "g", "x", "d", "e"})
    B2.add(S);

  cout << "Tree 2" << endl;
  cout << B2 << endl;

  cout << "Contains Test" << endl;
  bool contains = B2.contains("a");
  assert(contains);
  cout << "Contains Success" << endl;


  cout << "Remove Test" << endl;
  cout << "Remove a" << endl;
  bool remove = B2.remove("a");
  assert(remove);
  cout << B2 << endl;
  cout << "Remove a Success" << endl;

  cout << "Remove f" << endl;
  remove = B2.remove("f");
  assert(remove);
  cout << B2 << endl;
  cout << "Remove f Success" << endl;

  cout << "Remove g" << endl;
  remove = B2.remove("g");
  assert(remove);
  cout << B2 << endl;
  cout << "Remove g Success" << endl;


  cout << "Ending testSample01" << endl;


}

void arrayTest() {
  int *foo;
  foo = new int[10];

  for (int i = 0; i < 10; i++) {
    foo[i] = i + 1;
  }

  BST<int> B1(foo, 10);
  cout << B1 << endl;

  delete foo;
}

void constructorTest() {
  cout << "1 item constructor test" << endl;
  BST<int> B5(1);
  cout << B5 << endl;
  cout << "Passes" << endl;
}

// Calling all test functions
void testBSTAll() {
  //testPisan01();
  //testPisan02();
  //testPisan03();
  testSample01();
  arrayTest();
  constructorTest();
}