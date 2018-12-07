#ifndef MAZE_H
#define MAZE_H

#include "d_except.h"
#include "d_matrix.h"
#include "graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <limits.h>
#include <list>

using namespace std;

struct address
{
  int i;
  int j;
};

class maze
{
public:
  maze(ifstream &fin);
  void print(int, int, int, int);
  bool isLegal(int i, int j);
  bool isValid(int i, int j);

  void setMap(int i, int j, int n);
  int getMap(int i, int j) const;
  void pushNodeMap(int i, int j);
  void setNodeMap(int n, int i, int j);
  address getNodeMap(int n);
  void mapMazeToGraph(graph &g);

  int rows; // number of rows in the maze
  int cols; // number of columns in the maze

private:
  matrix<bool> value;
  vector<address> nodemap;
  matrix<int> map; // Mapping from maze (i,j) values to node index values
};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{
  map[i][j] = n;
  return;
}

int maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
  return map[i][j];
}

void maze::pushNodeMap(int i, int j)
{
  address temp;
  temp.i = i;
  temp.j = j;

  nodemap.push_back(temp);
}

void maze::setNodeMap(int n, int i, int j)
{
}

address maze::getNodeMap(int n)
{
  return nodemap[n];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
  fin >> rows;
  fin >> cols;

  char x;

  value.resize(rows, cols);
  for (int i = 0; i <= rows - 1; i++)
    for (int j = 0; j <= cols - 1; j++)
    {
      fin >> x;
      if (x == 'O')
        value[i][j] = true;
      else
        value[i][j] = false;
    }

  map.resize(rows, cols);
  nodemap.resize(0);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
  cout << endl;

  if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
    throw rangeError("Bad value in maze::print");

  if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
    throw rangeError("Bad value in maze::print");

  for (int i = 0; i <= rows - 1; i++)
  {
    for (int j = 0; j <= cols - 1; j++)
    {
      if (i == goalI && j == goalJ)
        cout << "*";
      else if (i == currI && j == currJ)
        cout << "+";
      else if (value[i][j])
        cout << " ";
      else
        cout << "X";
    }
    cout << endl;
  }
  cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
  if (i < 0 || i > rows || j < 0 || j > cols)
    throw rangeError("Bad value in maze::isLegal");

  return value[i][j];
}

bool maze::isValid(int i, int j)
// Return whether the cell is valid
{
  bool flag = true;
  if (i < 0 || i >= rows || j < 0 || j >= cols || value[i][j] == 0)
    flag = false;
  return flag;
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
  int nodeindex = 0;
  if (g.numNodes() || g.numEdges())
  {
    cout << "Unable to map graph. Graph is not empty." << endl;
    return;
  }
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
    {
      if (isValid(i, j))
      {
        g.addNode(0);
        setMap(i, j, nodeindex);
        pushNodeMap(i, j);
        nodeindex++;
      }
    }

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
    {
      if (isValid(i - 1, j)) // up
        g.addEdge(map[i][j], map[i - 1][j]);

      if (isValid(i + 1, j)) // down
        g.addEdge(map[i][j], map[i + 1][j]);

      if (isValid(i, j - 1)) // left
        g.addEdge(map[i][j], map[i][j - 1]);

      if (isValid(i, j + 1)) // right
        g.addEdge(map[i][j], map[i][j + 1]);
    }

  cout << "nodes = " << g.numNodes() << endl;
  cout << "edges = " << g.numEdges() << endl;
}

#endif