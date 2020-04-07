#include "kdtree.h"

int main(int argc, char const *argv[]) {
  axisCoordinate rootCoordinates = {20,3};
  axisCoordinate searchCoordinates = {20,3};
  KDTree<int> myKDTree(rootCoordinates);
  myKDTree.addRandomNodes(100,50);
  myKDTree.print();
  if(myKDTree.search(searchCoordinates)){cout << "FOUND!\n";}
  return 0;
}
