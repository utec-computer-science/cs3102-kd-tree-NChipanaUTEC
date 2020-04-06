#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
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
    cout <<"To Upper Node"<< endl;
  }

};

void insertNode(Node* root,vector<int>& newCoordinates,int dimension = 0){
  if(dimension == DIMENSIONS){dimension = 0;}
  int axisCoordinate = root->getCoordinate(dimension);
  if(axisCoordinate > newCoordinates[dimension]){
    if(root->hasLeftNode()){
      insertNode(root->getLeftNode(),newCoordinates,dimension+1);
    }
    else{
      Node* newNode = new Node(newCoordinates);
      root->assignLeftNode(newNode);
    }
  }
  else if(axisCoordinate <= newCoordinates[dimension]){
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
  srand(time(NULL));
  vector<int> rootCoordinates {20,3};
  vector<int> otherCoordinates;
  Node* root = createTree(rootCoordinates);
  for(int i = 0; i < 10; i++){
    otherCoordinates.push_back(rand()%25);
    otherCoordinates.push_back(rand()%25);
    insertNode(root,otherCoordinates);
    otherCoordinates.clear();
  }
  root->print();
  return 0;
}
