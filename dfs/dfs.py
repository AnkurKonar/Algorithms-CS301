time=0

file=open('dfs.txt','r')
edges=[]
edge=[]
for x in file.readlines():
    for i in x.split():
        edge.append(i)
    edges.append(edge)
    edge=[]

V=[]
for x in edges:
    if x[0] not in V:
        V.append(x[0])
    if x[1] not in V:
        V.append(x[1])

V.sort()
print(V)

status = [0]*len(V)
parent = [-1]*len(V)
discTime = [0]*len(V)
finishTime = [0]*len(V)

matrix = [[0 for i in range(len(V))] for j in range(len(V))]

for x in edges:
    matrix[V.index(x[0])][V.index(x[1])] = 1

def dfsVisit(v):
    status[v]=1
    global time
    time+=1
    discTime[v]=time
    for u in range(len(V)):
        if matrix[v][u]==1 and status[u]==0:
            parent[u]=v
            dfsVisit(u)
    time=time + 1
    status[v]=2
    finishTime[v]=time
    

for x in V:
    if status[V.index(x)]==0:
        dfsVisit(V.index(x))

print("Parent:", parent)
print("Discovery Time:",discTime)
print("finish Time:",finishTime)
print("Topological Sort: ")
for j in sorted(list(zip(V,finishTime)), key=lambda x: x[1],reverse=True):
    print(j[0],end=" ")
    