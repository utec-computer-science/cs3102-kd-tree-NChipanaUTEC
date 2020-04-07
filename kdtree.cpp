#include "kdtree.h"

int main(int argc, char const *argv[]) {
  axisCoordinate rootCoordinates = {20,3};
  KDTree<int> myKDTree(rootCoordinates);
  myKDTree.addRandomNodes(25,25);
  myKDTree.print();
  return 0;
}
