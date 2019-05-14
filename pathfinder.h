/*
  John Michael Hayde
  A* implementation (modified - only uses heuristic)
  Written in c++
*/

#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>

/*
  Helpful Structures
*/

//pair is x and y coordinates
typedef std::pair<int, int> Pair;

//holds start and end coordinates of the path
//end coordinates are needed for A* to calculate the heuristic
struct seCoord {
  Pair start;
  Pair end;
};

//holds data for each point on the maze - x,y coordinates, parent info, f,g,h cost
struct Point {
  //coordinate of node
  int x, y;
  //coordinate of parent to find path from end to start (store parent info as x,y difference to get from A to B)
  Pair parent;
  //h = Manhattan distance from current point to end
  int h;
};

/*
  Operator Overload
*/

//compares 2 points F cost for placement in priority queue (will order Nodes smallest to largest)
bool operator < (Point left, Point right) {
  return left.h < right.h;
}

/*
  Function Implementations
*/

//calculates the manhattan distance from current point to end point
int calcH(int x, int y, Pair end) {
  return (abs(x - end.first) + abs(y - end.second));
}

//finds the coordinates of the start and end characters
//returns their location as -1,-1 if either does not exist
template<std::size_t rows, std::size_t cols>
seCoord findPos(char (&maze)[rows][cols]) {
  //return var for points
  seCoord points;
  points.start = std::make_pair(-1,-1);
  points.end = std::make_pair(-1,-1);
  //loop through each row
  for(int i = 0; i < rows; i++) {
    //loop through each col
    for(int j = 0; j < cols; j++) {
      //set start coordinates
      if(maze[i][j] == 's') {
        points.start = std::make_pair(i, j);
      }
      //set end coordinates
      if(maze[i][j] == 'f') {
        points.end = std::make_pair(i, j);
      }
      //cuts off searching if both points have been found
      if(points.start.first != -1 && points.end.first != -1) {
        return points;
      }
    }
  }
  //default return
  return points;
}

//finds the path from start to end by subtracting the parent info from current x,y values
//parent info is stored as the change to get from one point to the next,
//so subtracting the change will reverse this (go end to start, reverse with stack)
std::vector<char> findPath(std::map<Pair, Point> &map, seCoord se) {
  //path to return
  std::vector<char> path;
  //stack to reverse order of path since going from end to start
  std::stack<char> temp_path;
  //start at end
  Pair coord;
  coord.first = se.end.first;
  coord.second = se.end.second;
  Point point = map.at(coord);
  //loop until start node is found (parent coordinates will be the same as current points coordinates)
  //have to check x,y together as one location (if checking separate, one correct value will break the loop. that was a fun bug to find)
  while(!(point.parent.first == se.start.first && point.parent.second == se.start.second)) {
    //find move (left, right, up, down) these are flippped since parent info represents the move from parent to point
    if(point.parent.first == 0 && point.parent.second == 1) {
      temp_path.push('R');
    }
    else if(point.parent.first == 0 && point.parent.second == -1) {
      temp_path.push('L');
    }
    else if(point.parent.first == -1 && point.parent.second == 0) {
      temp_path.push('U');
    }
    else {
      temp_path.push('D');
    }
    //update location of node based on parent data (subtract since parent info is change in x,y
    //to get to current point, so subtracting change will move in opposite direction it took to get from parent to point
    coord.first -= point.parent.first;
    coord.second -= point.parent.second;
    //update points location
    point = map.at(coord);
  }
  //move data from stack to vector since order of moves is from end to start
  while(temp_path.size() > 0) {
    path.push_back(temp_path.top());
    temp_path.pop();
  }
  return path;
}

//performs a greedy alteration of a* algorithm
template<std::size_t rows, std::size_t cols>
std::vector<char> pathfinder(char (&maze)[rows][cols]) {
  //unordered_map to hold Point version of maze
  std::map<Pair, Point> superMaze;
  //keeps track of visited values like in Dijksstra's
  std::set<Point> visitedPoints;
  //return vector containing path from start to end
  std::vector<char> path;
  //priority queue keeps track of next node based on lowest h cost like Dijkstra's with lowest distance
  //uses operator < function for insertion
  std::priority_queue<Point> nextPoints;
  //find start and end coordinates
  seCoord se = findPos(maze);
  //make sure start is valid point, if not return empty vector
  if(se.start.first == -1) {
    path.push_back('\0');
    return path;
  }
  //make sure end is valid point, if not return empty vector
  else if(se.end.first == -1) {
    path.push_back('\0');
    return path;
  }
  //initialize superMaze with same coordinate plane as maze with basic values
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      //temp Point for insertion
      Point temp;
      temp.x = i;
      temp.y = j;
      //start parents at invalid moves
      temp.parent.first = -2;
      temp.parent.second = -2;
      //h cost starts at infinite like Dijkstra's
      temp.h = 10000000;
      //pair data type to hold x,y coordinates for hash
      Pair tempPair;
      tempPair.first = temp.x;
      tempPair.second = temp.y;
      //initialize supermaze at location x,y
      superMaze.insert(std::make_pair(tempPair, temp));
    }
  }
  //now we need to initialize the start point
  //get start coordinates
  Pair tempPair;
  tempPair.first = se.start.first;
  tempPair.second = se.start.second;
  //set cost to 0 since it is start
  superMaze.at(tempPair).h = 0;
  //set parent coordinates to itself (will be base case for looping back from end to start)
  superMaze.at(tempPair).parent = tempPair;
  //add start point to nextPoints list to start loop
  nextPoints.push(superMaze.at(tempPair));
  //loop while there are possible Points to check
  while(nextPoints.size() > 0) {
    //pull Point from top of nextPoints list
    Point currentPoint = nextPoints.top();
    //remove it from the list (accidentally putting top() instead of pop() will make for a fun night of debugging)
    nextPoints.pop();
    //add it to visitedPoints set
    visitedPoints.insert(currentPoint);
    //vectors for change in x,y to check left,right,up,down from current position
    //add same index of both vectors to current x,y to get position of surrounding points
    std::vector<int> xArr = {-1,1,0,0};
    std::vector<int> yArr = {0,0,-1,1};
    //loop through points surrounding currentPoint
    for(int i = 0; i < xArr.size(); i++) {
      //find updated x and y locations based on change from xArr and yArr
      Pair updatedPoint;
      updatedPoint.first = currentPoint.x + xArr.at(i);
      updatedPoint.second = currentPoint.y + yArr.at(i);
      //check to see if this point is a valid position on the maze coordinate plane
      //this statement will also check to see if this position == 'w' in the maze
      //and will say the position is invalid if it is a 'w', since we can't move through walls
      if((superMaze.count(updatedPoint) > 0) && (maze[updatedPoint.first][updatedPoint.second] != 'w')) {
        //since it's a valid option, need to check if it's already been visited
        //comes after validity statement since invalid Point will be unvisited and seg fault
        if(visitedPoints.find(superMaze.at(updatedPoint)) == visitedPoints.end()) {
          //point has not been visited, check if we have found the end
          if((updatedPoint.first == se.end.first) && (updatedPoint.second == se.end.second)) {
            //we have found the end
            //find change in x,y to get to final point
            Pair parentInfo;
            parentInfo.first = xArr.at(i);
            parentInfo.second = yArr.at(i);
            //update final Points parent data (unable to trace path back without this, not a fun bug to find)
            superMaze.at(updatedPoint).parent = parentInfo;
            //find path and return
            path = findPath(superMaze, se);
            return path;
          }
          //point has not been visited but is not the end, check h cost and possibly add to nextPoints queue
          else {
            //not end but unvisited point, find h cost
            int h = calcH(updatedPoint.first, updatedPoint.second, se.end);
            //check if new h is better than what was previously set for updatedPoint
            if(h < superMaze.at(updatedPoint).h) {
              //found better path to this Point, update info
              superMaze.at(updatedPoint).h = h;
              //update parent info
              Pair parentInfo;
              parentInfo.first = xArr.at(i);
              parentInfo.second = yArr.at(i);
              superMaze.at(updatedPoint).parent = parentInfo;
              //add Point to nextPoints queue
              nextPoints.push(superMaze.at(updatedPoint));
            }
          }
        }
      }
    }
  }
  //to get rid of the annoying "control may reach end of non-void function warning", and base case if no path is found
  path.push_back('\0');
  return path;
}
