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
        cout<<coordinates[i]<<" ";
      }
      cout << endl;
      if(this->left){
        cout <<"To Left Node\n";
        left->print();
      }
      if(this->right){
        cout <<"To Right Node\n";
        right->print();
      }
      cout <<"To Upper Node\n";
    }

  };
private:
  Node* root;
  int totalNodes;

public:
  KDTree(axisCoordinate& rootCoordinates){
    root = new Node(rootCoordinates);
    totalNodes = 1;
  }

  void insertNode(axisCoordinate& newCoordinates){
    insertNodeRecursive(root,newCoordinates);
    totalNodes ++;
  }

  void insertNodeRecursive(Node* currentNode,axisCoordinate& newCoordinates,T dimension = 0){
    if(dimension == DIMENSIONS){dimension = 0;}
    T point = root->getPoint(dimension);
    if(point > newCoordinates[dimension]){
      if(currentNode->left){
        insertNodeRecursive(currentNode->left,newCoordinates,dimension+1);
      }
      else{
        Node* newNode = new Node(newCoordinates);
        currentNode->left = newNode;
      }
    }
    else if(point <= newCoordinates[dimension]){
      if(currentNode->right){
        insertNodeRecursive(currentNode->right,newCoordinates,dimension+1);
      }
      else{
        Node* newNode = new Node(newCoordinates);
        currentNode->right = newNode;
      }
    }
  }

  void addRandomNodes(T amountNodes,T limit = 25){
    srand(time(NULL));
    axisCoordinate newCoordinates;
    for(int i = 0; i < amountNodes; i++){
      newCoordinates = {rand()%limit,rand()%limit};
      insertNode(newCoordinates);
      newCoordinates.clear();
    }
  }

  void print(){
    cout <<"KD-Tree:\n";
    root->print();
    cout << "\n";
  }

  int size(){
    return totalNodes;
  }
};
