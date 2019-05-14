/*
  John Michael Hayde
  for testing pathfinding program
*/

#include "pathfinder.h"

int main() {

  //simple maze
  // char arr[5][5] =
  // {
  //   {'s', 'e', 'e', 'e', 'e'},
  //   {'e', 'e', 'e', 'e', 'e'},
  //   {'e', 'e', 'e', 'e', 'e'},
  //   {'e', 'e', 'e', 'f', 'e'},
  //   {'e', 'e', 'e', 'e', 'e'}
  // };

  //complex maze without bombs/coins
  // char arr[15][20]=
  // {
  // {'s','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
  // {'e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
  // {'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','w','w'},
  // {'e','w','e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','w','e','e'},
  // {'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','e','e'},
  // {'e','w','e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','w','e','e'},
  // {'e','w','e','w','e','w','w','w','w','w','w','w','e','e','e','e','e','w','e','e'},
  // {'e','w','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','w','w','e'},
  // {'e','w','e','w','e','e','e','e','e','e','w','w','e','w','e','e','e','e','w','e'},
  // {'e','w','e','w','e','e','e','f','e','e','w','e','e','w','e','w','w','e','w','e'},
  // {'e','w','e','w','e','e','e','e','e','e','w','e','e','w','e','e','w','e','w','e'},
  // {'e','w','e','w','e','e','e','e','e','e','w','w','e','w','e','e','w','e','e','e'},
  // {'e','w','e','w','e','e','e','e','e','e','e','w','e','w','e','e','w','e','e','e'},
  // {'e','e','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','e','e','e'},
  // {'e','w','e','w','e','e','e','e','e','e','w','e','e','e','e','e','e','e','e','e'},};
  //

  //complex maze without bombs/coins
  char arr[15][20] = {
    {'s','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
    {'e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
    {'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','w','w'},
    {'e','w','e','w','b','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},
    {'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','g','g'},
    {'e','w','e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},
    {'e','w','e','w','e','w','w','w','w','w','w','w','e','e','e','e','e','w','g','g'},
    {'e','w','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','w','w','e'},
    {'e','w','e','w','e','e','b','e','e','e','w','w','e','w','e','e','e','e','w','e'},
    {'e','w','e','w','e','g','b','f','e','e','w','e','e','w','e','w','w','e','w','e'},
    {'e','w','e','w','e','e','b','e','g','g','w','e','e','w','e','e','w','e','w','e'},
    {'e','w','e','w','e','e','e','e','e','e','w','w','e','w','e','e','w','e','e','e'},
    {'e','w','e','w','e','e','e','e','e','e','e','w','e','w','e','e','w','e','e','e'},
    {'e','e','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','e','e','e'},
    {'e','w','e','w','e','e','e','e','e','e','w','e','e','e','e','e','e','e','e','e'},
  };

  //tests pathfinding funciton with arr
  std::vector<char> path = pathfinder(arr);

  //prints out each move made from start to end
  int moves = 0;
  for(int i = 0; i < path.size(); i++) {
    std::cout << path.at(i) << std::endl;
    moves++;
  }
  std::cout << "numer of steps: " << moves << std::endl;

  return 0;

}
