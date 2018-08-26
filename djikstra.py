#CODE OF DJIKSTRA ALGORITHM IN PYTHON3

#
#
#
#               ->|B|----------4--------->|D|-
#              /    |                 //  /   \
#             /     |              //   /      \
#            5      |            //    /        12
#           /       |          //    /           \
#          /        |        //    3              V
#       |A|<--\     1       2    /               |F|
#          \   \    |     //    /                ^
#           \   \   |   //    /                 /
#            10  3  |  //   /                  3
#             \  |  | //  /                   /
#              \ |  V<---/                   /
#               ->|C|-----------2-------->|E|
#
#
#
#
#
#



#INPUT GRAPH

graph=[
        [0,5,10,0,0,0],
        [0,0,1,4,0,0],
        [3,0,0,2,2,0],
        [0,0,3,0,0,12],
        [0,0,0,0,0,3],
        [0,0,0,0,0,0]
        ]

#ASSINGNED INTEGER
nodes=[['A',0],['B',1],['C',2],['D',3],['E',4],['F',5]]

#INPUT FOR THE START
x=input("ENTER THE STARTING NODE(A/B/C/D/E/F): ")
start_node=-1

#Searches the node and assigns the index to start_node

for i in nodes:
    if x==i[0]:
        start_node=i[1]


#INPUT FOR THE END

x=input("ENTER THE ENDING NODE(A/B/C/D/E/F): ")
end_node=-1

#searches the node and assigns the index to end_node
for i in nodes:
    if x==i[0]:
        end_node=i[1]

#FUNCTION TO FIND THE MINIMUM EXCLUDING THE ONES ALREADY CONSIDERED
def mini(pl,considered):
    minimum=10000
    minimum_index=-1
    for x in range(6):
        if x not in considered:
            if(pl[x]<minimum):
                minimum=pl[x]
                minimum_index=x
    return minimum_index

#FUNCTION TO PRINT THE FINAL LIST
def printFinal(l,j):
    if j==0:
        print(nodes[j][0])
        printFinal(l,l[j])
    elif j!=-1:
        print(nodes[j][0],"<- ",end="")
        printFinal(l,l[j])


#THE ENTIRE PATH LIST
pathlist=[0,0,0,0,0,0]


#INDEXES THAT HAVE BEEN CONSIDERED
finished=[]


#FINAL PATH
final_path=[-1,-1,-1,-1,-1,-1]

#ASSIGNING THE FIRST SET OF VALUES IN ENTIRE PATH LIST
pathlist[start_node]=0
for i in range(1,6):
    if i==start_node:
        pathlist[start_node]=0
    elif(graph[start_node][i]==0):
        pathlist[i]=10000
    else:
        pathlist[i]=graph[start_node][i]
        final_path[i]=start_node

#Added the start node to the finished set
finished.append(start_node)

#DJIKSTRA LOOP

while len(finished)!=6:
    u=mini(pathlist,finished)
    for i in range(0,6):
        if(graph[u][i]==0):
            val=10000
        else:
            val=graph[u][i]
            if pathlist[i]>(pathlist[u]+val):
                final_path[i]=u
        pathlist[i]=min(pathlist[i], (pathlist[u]+val))
    finished.append(u)

printFinal(final_path,end_node)
print("The minimum path weight: ", pathlist[end_node])
        
        
        