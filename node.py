import numpy as np

class Node:
    
    #intialize the node with the board config
    def __init__(self, s):  
        self.child = s
        self.parent = None
        self.gn = 0
        self.hn = 0
        self.fn = 0

    def get_parent(self):
        return self.parent
    
    def get_hn(self):
        return self.hn
    
    def get_fn(self):
        return self.gn + self.hn
    
    def get_gn(self):
        return self.gn
    
    def get_current_state(self):
        return self.child
    
    def update_gn(self, gn):
        self.gn=gn
        
    def update_hn(self, hn):
        self.hn=hn
    
    def update_parent(self, parent):
        self.parent= parent
    
    #exploring the next states
    def expand_node(fringe, explored_nodes, current_node, goal_node, zero, g, count,heuristic):
        a                   =   [ list(item.get_current_state()) for item in explored_nodes ]
        explored_nodes.append(current_node)
        current_node_array  =   np.asarray(current_node.get_current_state())
    #since the left tile cannot be moved left
    #edge case for moving the left tile
        if zero != 0 and zero!=3 and zero!=6:
            node_copy           =   current_node_array.copy()
            temp                =   node_copy[zero-1]
            node_copy[zero-1]   =   current_node_array[zero]
            node_copy[zero]     =   temp
            distance            =   Distance.distance(node_copy,goal_node,heuristic)
            count               =   count+1
            
            if not list(node_copy) in a:
                node_copy = Node(node_copy)
                node_copy.update_gn(g)
                node_copy.update_hn(distance)            
                node_copy.update_parent(current_node)
                fringe.append(node_copy)
    
    #since the bottom tile cannot be moved down
    #edge case for moving the bottom tile   
        if zero!=6 and zero!=7 and zero!=8:
            node_copy           =   current_node_array.copy()
            temp                =   node_copy[zero+3]
            node_copy[zero+3]   =   current_node_array[zero]
            node_copy[zero]     =   temp
            distance            =   Distance.distance(node_copy,goal_node,heuristic)
            count               =   count+1
            if not list(node_copy) in a:
                node_copy       =   Node(node_copy)
                node_copy.update_gn(g)
                node_copy.update_hn(distance)            
                node_copy.update_parent(current_node)
                fringe.append(node_copy)
    #since the top tiles cannot be moved up
    #edge case for moving the top tile 
        if zero != 0 and zero!=1 and zero!=2:
            node_copy           =   current_node_array.copy()
            temp                =   node_copy[zero-3]
            node_copy[zero-3]   =   current_node_array[zero]
            node_copy[zero]     =   temp
            distance            =   Distance.distance(node_copy,goal_node,heuristic)
            count               =   count+1
            if not list(node_copy) in a:
                node_copy=Node(node_copy)
                node_copy.update_gn(g)
                node_copy.update_hn(distance)            
                node_copy.update_parent(current_node)
                fringe.append(node_copy)
    
    #since the right tiles cannot be moved right
    #edge case for moving the right tiles 
        if zero != 2 and zero!=5 and zero!=8:
            node_copy           =   current_node_array.copy()
            temp                =   node_copy[zero+1]
            node_copy[zero+1]   =   current_node_array[zero]
            node_copy[zero]     =   temp
            distance            =   Distance.distance(node_copy,goal_node,heuristic)
            count               =   count+1
            if not list(node_copy) in a:
                node_copy       =   Node(node_copy)
                node_copy.update_gn(g)
                node_copy.update_hn(distance)            
                node_copy.update_parent(current_node)
                fringe.append(node_copy)
        return count
            
class Puzzle:
    
    def least_fn(fringe):
        fn_fringe           =   []
        for i in range(len(fringe)):
            fn_fringe.append(fringe[i].get_fn())
        minimum_fn          =   min(fn_fringe)
        minimum_fn_index    =   fn_fringe.index(minimum_fn)
        return minimum_fn_index
        
    def print_state(node):
        print("g(n) = ", node.get_gn(), " h(n) = ", node.get_hn(), " f(n) = ", node.get_fn() ,"\n")
        print(node.get_current_state()[0] , " | " , node.get_current_state()[1] , " | "
                , node.get_current_state()[2]);
        print("--------------");
        print(node.get_current_state()[3] , " | " , node.get_current_state()[4] , " | "
                , node.get_current_state()[5]);
        print("--------------");
        print(node.get_current_state()[6] , " | " , node.get_current_state()[7] , " | "
                , node.get_current_state()[8]);
        print("----------------------------------------------------------\n")
        
    def goal_reached(explored_nodes, count):
        nodes_expanded  =   len(explored_nodes)-1
        path            =   []
        init            =   explored_nodes[0]
        current         =   explored_nodes.pop()
        
        while init!=current:
            path.append(current)
            current = current.get_parent()
        
        path.append(init)
        path.reverse()
        
        for i in path:
            Puzzle.print_state(i)
        
        print("Goal Reached \n")
        print("The number of nodes expanded: " , nodes_expanded, "\n")
        print("The number of nodes generated: ", count, "\n");
        print("Path Cost: ", len(path)-1, "\n");
        
    def path(explored_nodes):
        explored_nodes.pop()

#Distance Class to Calculate the Manhattan Distance and Misplaced Tiles.

class Distance:
    
    def distance(arr, goal, heuristic):
        distance = 0
        if heuristic == 1:
            for i in range(8):
                if arr[i]!=goal[i]:
                    distance=distance+1
            return distance
        elif heuristic == 2:
            arr     = np.asarray(arr).reshape(3,3)
            goal    = np.asarray(goal).reshape(3,3)
            for i in range(8):
                a,b      = np.where(arr == i+1)
                x,y      = np.where(goal == i+1)
                distance = distance + abs((a-x)[0])+abs((b-y)[0])
            return distance