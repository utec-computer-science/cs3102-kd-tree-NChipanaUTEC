#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#define DIMENSIONS 2
#define axisCoordinate vector<int>
using namespace std;

template<typename T>
class KDTree{
  struct Node{
    axisCoordinate coordinates;
    Node* left;
    Node* right;

    Node():left(NULL),right(NULL){}
    Node (axisCoordinate newCoordinates):coordinates(newCoordinates),left(NULL),right(NULL){}

    T getPoint(T dimension){
      return coordinates[dimension];
    }

    void print(){
      for(int i = 0; i < coordinates.size(); i++){
        cout << coordinates[i]<<" ";
      }
      cout <<"\n";
    }

    void printTree(){
      print();
      if(this->left){
        cout <<"To Left Node\n";
        left->printTree();
      }
      if(this->right){
        cout <<"To Right Node\n";
        right->printTree();
      }
      cout <<"To Upper Node\n";
    }

  };
private:
  Node* root;
  int totalNodes;

public:
  // Creates a KD-Tree with an initial Node
  KDTree(axisCoordinate& rootCoordinates){
    root = new Node(rootCoordinates);
    totalNodes = 1;
  }

  // Creates an empty KD-Tree
  KDTree(){
    root = NULL;
    totalNodes = 0;
  }

  int size(){
    return totalNodes;
  }

  // First Insertion function called
  void insertNode(axisCoordinate& newCoordinates){
    insertNodeRecursive(root,newCoordinates);
    totalNodes ++;
  }

  // This insertion is used to be called recursively
  void insertNodeRecursive(Node* currentNode,axisCoordinate& newCoordinates,T dimension = 0){
    // If the current dimension is the highest dimension possible, then reset.
    if(dimension == DIMENSIONS){dimension = 0;}
    // Get the coordinate in the position of the current dimension of the current Node.
    T point = currentNode->getPoint(dimension);
    // If/Else that determines if its higher or lower than the current Node.
    if(newCoordinates[dimension] < point){
      if(currentNode->left){
        // Calls this function again with the next Node and a higher dimension.
        insertNodeRecursive(currentNode->left,newCoordinates,dimension+1);
      }
      else{
        // Creates and assigns new Node
        Node* newNode = new Node(newCoordinates);
        currentNode->left = newNode;
      }
    }
    else if(newCoordinates[dimension] >= point){
      if(currentNode->right){
        // Calls this function again with the next Node and a higher dimension.
        insertNodeRecursive(currentNode->right,newCoordinates,dimension+1);
      }
      else{
        // Creates and assigns new Node
        Node* newNode = new Node(newCoordinates);
        currentNode->right = newNode;
      }
    }
  }

  // Adds a determined amount of nodes with a random value with another determined threshold.
  void addRandomNodes(T amountNodes,T limit = 25){
    srand(time(NULL));
    //Creates new axisCoordinate variable to be used in loop.
    axisCoordinate newCoordinates;
    for(int i = 0; i < amountNodes; i++){
      // Sets two random values for the first and second positions of the axisCoordinate using a threshold.
      newCoordinates = {rand()%limit,rand()%limit};
      insertNode(newCoordinates);
      newCoordinates.clear();
    }
  }

  //Not Working - In Development
  void nearestNeighbor(axisCoordinate& searchPoint){
    cout << "Searching for neighrest neighbor of ";
    for(int i = 0; i < searchPoint.size(); i++){
      cout << searchPoint[i]<<" ";
    }
    cout <<"\n";

    bool found = false;
    Node* currentNode = root;
    T dimension = 0;
    T point = currentNode->getPoint(dimension);
    while(!found){
      if(dimension == DIMENSIONS){dimension = 0;}
      if(!currentNode->left && !currentNode->right){
        currentNode->print();
        found = true;
        break;
      }
      else if(point > searchPoint[dimension]){
        if(currentNode->left){
          currentNode = currentNode->left;
          dimension++;
        }
        else{
          currentNode->print();
          found = true;
          break;
        }
      }
      else if(point <= searchPoint[dimension]){
        if(currentNode->right){
          currentNode = currentNode->right;
          dimension++;
        }
        else{
          currentNode->print();
          found = true;
        }
      }
    }
  }

  //Calls the printTree function inside the Node structure
  void print(){
    cout <<"KD-Tree:\n";
    root->printTree();
    cout << "\n";
  }
};
