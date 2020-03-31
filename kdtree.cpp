#include <iostream>
#include <vector>
#define DIMENSIONS 2
using namespace std;


class Node{
  vector<int> coordinates;
  Node* left;
  Node* right;
public:
  Node (vector<int> newCoordinates):coordinates(newCoordinates),left(NULL),right(NULL){}

  bool hasRightNode(){
    return right != NULL;
  }

  Node* getRightNode(){
    return right;
  }

  void assignRightNode(Node* newNode){
    right = newNode;
  }

  bool hasLeftNode(){
    return left != NULL;
  }

  Node* getLeftNode(){
    return left;
  }

  void assignLeftNode(Node* newNode){
    left = newNode;
  }

  int getCoordinate(int dimension){
    return coordinates[dimension];
  }

  void print(){
    for(int i = 0; i < coordinates.size(); i++){
      cout<<coordinates[i]<<" ";
    }
    cout << endl;
    if(hasLeftNode()){
      cout <<"To Left Node"<< endl;
      getLeftNode()->print();
    }
    if(hasRightNode()){
      cout <<"To Right Node"<< endl;
      getRightNode()->print();
    }
  }

};

void insertNode(Node* root,vector<int>& newCoordinates,int dimension){
  if(dimension == DIMENSIONS){dimension = 0;}
  int axisCoordinate = root->getCoordinate(dimension);
  if(axisCoordinate < newCoordinates[dimension]){
    if(root->hasLeftNode()){
      insertNode(root->getLeftNode(),newCoordinates,dimension+1);
    }
    else{
      Node* newNode = new Node(newCoordinates);
      root->assignLeftNode(newNode);
    }
  }
  else if(axisCoordinate > newCoordinates[dimension] || axisCoordinate == newCoordinates[dimension]){
    if(root->hasRightNode()){
      insertNode(root->getRightNode(),newCoordinates,dimension+1);
    }
    else{
      Node* newNode = new Node(newCoordinates);
      root->assignRightNode(newNode);
    }
  }
}

Node* createTree(vector<int>& point){
  Node* root = new Node(point);
  return root;
}

int main(int argc, char const *argv[]) {
  vector<int> rootCoordinates {20,3,1,3};
  vector<int> otherCoordinates {10,2,4,2};
  vector<int> otherCoordinates2 {25,1,3,2};
  Node* root = createTree(rootCoordinates);
  insertNode(root,otherCoordinates,0);
  insertNode(root,otherCoordinates2,0);
  root->print();
  return 0;
}
