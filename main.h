#if (1)

#include <stack>
#include "maze.h"

using namespace std;

stack<NodeType> path;

bool dfs(graph &g, NodeType v, NodeType dest)
{
  g.visit(v);
  int count = 0;

  if (v == dest)
  {
    cout << "found a path" << endl;
    path.push(v);
    return true;
  }


  NodeType i = 0;
  while (i < g.numNodes() && count < 3)
  {
    if (g.isEdge(v, i))
    {
      if (!g.isVisited(i))
      {
        count++;
        if(dfs(g, i, dest))
        {
            path.push(v);
            return true;
        }
      }
    }
    i++;
  }
  return false;
}

void solveMaze(maze &m, graph &g)
{
    m.mapMazeToGraph(g);
    int index = 0;
    int dest = m.getMap(m.rows-1, m.cols-1);
    g.clearVisit();
    dfs(g, index, dest);
    int size = path.size();
    for(int i = 0; i < size; i++)
    {
        cout << path.top() << endl;
        path.pop();
    }
}

#endif