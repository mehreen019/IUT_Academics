from collections import defaultdict

class Graph:
    def __init__(self, vertices):
        self.graph = defaultdict(list)
        self.V = vertices

    def addEdge(self, u, v):
        self.graph[u].append(v)
    
    def DFS(self, s):
        visited = [False] * self.V
        stack = []
        stack.append(s)
        visited[s] = True
        
        while stack:
            s = stack.pop()
            print(s, end=" ")
            
            for i in self.graph[s]:
                if visited[i] == False:
                    visited[i] = True
                    stack.append(i)
        return visited

g = Graph(5)
g.addEdge(0, 1)
g.addEdge(0, 2)
g.addEdge(1, 2)     
g.addEdge(2, 3)
g.addEdge(3, 1)
g.addEdge(3, 4)
g.addEdge(4, 0)
g.addEdge(4, 1)
g.addEdge(4, 2)
g.addEdge(4, 3)

g.DFS(0)