def BFS(graph,s, t, parent):  
    visited =[False]*(len(graph)) 
    # Create a queue for BFS 
    queue=[] 
    queue.append(s) 
    visited[s] = True
       
     # Standard BFS Loop 
    while queue: 
        u = queue.pop(0)  
        for i, val in enumerate(graph[u]): 
            if visited[i] == False and val > 0 : 
                queue.append(i) 
                visited[i] = True
                parent[i] = u  
    return True if visited[t] else False

# Returns tne maximum flow from s to t in the given graph 
def FordFulkerson(graph, source, terminal):
    parent = [-1]*(len(graph))
    max_flow = 0 
    # Augment the flow while there is path from source to sink 
    while BFS(graph, source, terminal, parent):  
        path_flow = 999999 
        s = terminal
        while(s !=  source): 
            path_flow = min (path_flow, graph[parent[s]][s]) 
            s = parent[s] 
        max_flow +=  path_flow 

        v = terminal
        while(v !=  source): 
            u = parent[v] 
            graph[u][v] -= path_flow 
            graph[v][u] += path_flow 
            v = parent[v] 
    return max_flow
  
graph = [[0, 3, 0, 5, 0, 2, 0, 0],
        [0, 0, 2, 0, 0, 0, 0, 4],
        [0, 0, 0, 0, 2, 0, 0, 3], 
        [0, 0, 0, 0, 4, 3, 0, 0], 
        [0, 5, 0, 0, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0, 0, 4, 0], 
        [0, 0, 0, 0, 0, 0, 0, 3], 
        [0, 0, 0, 0, 0, 0, 0, 0]]  
  
source = 0
terminal = 7
   
print ("The maximum possible flow is %d " %FordFulkerson(graph, source, terminal))
