#if (1)

#include <stack>
#include <vector>
#include <queue>
#include "maze.h"

using namespace std;

stack<NodeType> path;
vector<NodeType> pathtrans;
vector<stack<NodeType>> paths;

stack<NodeType> dfsStack;
queue<NodeType> bfsq;

void directions(maze &m, address add, address next)
{
  if(add.i >= m.rows-1 && add.j >= m.cols-1)
  {
    cout << "End of Path" << endl;
    return;
  }

  if(next.i - add.i == 0 && next.j -add.j == 1)
  {
    cout << "Move to the right" << endl;
  }

  if(next.i - add.i == 0 && next.j -add.j == -1)
  {
    cout << "Move to the left" << endl;
  }

  if(next.i - add.i == 1 && next.j -add.j == 0)
  {
    cout << "Move down" << endl;
  }

  if(next.i - add.i == -1 && next.j -add.j == 0)
  {
    cout << "Move up" << endl;
  }

}


void bfs(graph &g, NodeType dest)
{
  g.clearVisit();
  bfsq.push(0);
  g.visit(0);

  NodeType v;

  while(!bfsq.empty())
  {
    v = bfsq.front();

  }


}



void dfs(graph &g, NodeType dest)
{
  g.clearVisit();
  g.visit(0);
  dfsStack.push(0);
  int v;
  NodeType i = 0;
  while(!dfsStack.empty() && dfsStack.top() != dest)
  {
    v = dfsStack.top();
    i = 0;
    while (i < g.numNodes())
    {
      if (g.isEdge(v, i))
      {
        if (!g.isVisited(i))
        {
          g.visit(i);
          dfsStack.push(i);
          break;
        }
      }
      i++;
      if(i == g.numNodes())
        dfsStack.pop();
    }
    if(dfsStack.top() == dest)
      break;
  }  
  return;
}


bool dfsr(graph &g, NodeType v, NodeType dest)
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
        if (dfsr(g, i, dest))
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


void solveMazeDFS(maze &m, graph &g)
{
  
}

void solveMazeDFSR(maze &m, graph &g)
{
  address temp1, temp2;
  m.mapMazeToGraph(g);
  int index = 0;
  int dest = m.getMap(m.rows - 1, m.cols - 1);
  g.clearVisit();
  dfsr(g, index, dest);
  int size = path.size();
  pathtrans.resize(size);
  for (int i = 0; i < size; i++)
  {
    pathtrans.at(i) = path.top();
    path.pop();
  }

  for (int i = 0; i < size; i++)
  {
    temp1 = m.getNodeMap(pathtrans.at(i));
    if(i < size-1)
    {
      temp2 = m.getNodeMap(pathtrans.at(i+1));
      cout << pathtrans.at(i) << "  ";
      directions (m, temp1, temp2);
    }
    
    else
    {
      cout << "End" << endl;
    }
  }

}

#endif