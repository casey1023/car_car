from node import *
import numpy as np
import csv
import pandas
from enum import IntEnum
import math


class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5

class Maze:
    def __init__(self, filepath):
        # TODO : read file and implement a data structure you like
		# For example, when parsing raw_data, you may create several Node objects.  
		# Then you can store these objects into self.nodes.  
		# Finally, add to nd_dict by {key(index): value(corresponding node)}
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = []
        self.nd_dict = dict()  # key: index, value: the correspond node
        self.unexplored_deadend = []
        for i in range(len(self.raw_data)):
            self.nodes.append(Node(int(self.raw_data[i][0])))
    
        for i in range(len(self.raw_data)):
            self.nd_dict[int(self.nodes[i].getIndex())] = self.nodes[i]
            for j in range(1, 5):
                if self.raw_data[i][j] == self.raw_data[i][j]:
                    self.nodes[i].setSuccessor(self.nodes[int(self.raw_data[i][j])-1], Direction(j), self.raw_data[i][j+4])

    def getStartPoint(self):
        if (len(self.nd_dict) < 2):
            print("Error: the start point is not included.")
            return 0
        return self.nd_dict[1]
    
    def find_unexplored_deadend(self):
        temp = [self.getStartPoint()]
        walked = [-1 for i in range(len(self.nodes) + 1)]
        
        while len(temp) > 0:
            next = temp[0].getSuccessors()

            for i in next:
                check = i[0].getSuccessors()

                #encounter deadend
                if len(check) == 1 and check[0][0] == temp[0] and walked[i[0].getIndex()] == -1 and i[0] not in self.unexplored_deadend:
                    walked[i[0].getIndex()] = 1
                    self.unexplored_deadend.append(i[0])
                    temp.append(i[0]) 
                #unwalked node
                elif walked[i[0].getIndex()] == -1:
                    walked[i[0].getIndex()] = 1
                    temp.append(i[0])
            
            del temp[0]
        return None


    def getNodeDict(self):
        return self.nd_dict

    def BFS(self, nd):
        # TODO : design your data structure here for your algorithm
        # Tips : return a sequence of nodes from the node to the nearest unexplored deadend
        temp = [self.nd_dict[nd]]
        len_map = [-1 for i in range(len(self.raw_data) + 1)]
        len_map[temp[0].getIndex()] = 0

        deadend = Node()
        find_deadend = False

        while len(temp) and find_deadend == False:
            #print(temp[0].getIndex())
            next = temp[0].getSuccessors()

            #encounter deadend
            for i in next:
                check = i[0].getSuccessors()
                #print(check[0] , temp[0])
                if len(check) == 1 and check[0][0] == temp[0] and len_map[i[0].getIndex()] != 0:
                    len_map[i[0].getIndex()] = len_map[temp[0].getIndex()] + i[2]
                    deadend = i[0]
                    find_deadend = True
                    break

            #find and add next node
            for i in next:
                if len_map[i[0].getIndex()] == -1:
                    len_map[i[0].getIndex()] = len_map[temp[0].getIndex()] + i[2]
                    temp.append(i[0])
                elif len_map[i[0].getIndex()] != -1 and len_map[temp[0].getIndex()] + i[2] < len_map[i[0].getIndex()]:
                    len_map[i[0].getIndex()] = len_map[temp[0].getIndex()] + i[2]
                    temp.append(i[0])
            del temp[0]
        
        #backtracking
        #print("deadend "+str(deadend.getIndex())+"   "+str(len_map[deadend.getIndex()]))
        ans = [deadend]
        curent_node = deadend
        while len_map[curent_node.getIndex()] != 0:
            next = curent_node.getSuccessors()
            for i in next:
                if len_map[i[0].getIndex()] != -1 and len_map[i[0].getIndex()] < len_map[curent_node.getIndex()]:
                    ans.append(i[0])
                    curent_node = i[0]
                    break
        ans.reverse()
        return ans

    def BFS_2(self, nd_from, nd_to):
        # TODO : similar to BFS but with fixed start point and end point
        # Tips : return a sequence of nodes of the shortest path
        len_map = [-1 for i in range(len(self.nodes) + 1)]
        len_map[nd_from] = 0
        temp = [self.nd_dict[nd_from]]
        
        #BFS
        while len(temp) > 0:
            next = temp[0].getSuccessors()

            for i in next:
                if len_map[i[0].getIndex()] == -1:
                    len_map[i[0].getIndex()] = len_map[temp[0].getIndex()] + i[2]
                    temp.append(i[0])
                elif len_map[i[0].getIndex()] > len_map[temp[0].getIndex()] + i[2]:
                    len_map[i[0].getIndex()] = len_map[temp[0].getIndex()] + i[2]
                    temp.append(i[0])
            
            del temp[0]

        #backtracking
        cur_point = self.nd_dict[nd_to]
        ans = [cur_point]
        while len_map[cur_point.getIndex()] > 0:
            next = cur_point.getSuccessors()
            
            for i in next:
                if len_map[i[0].getIndex()] != -1 and len_map[i[0].getIndex()] < len_map[cur_point.getIndex()]:
                    cur_point = i[0]
                    ans.append(i[0])
                    break
        ans.reverse()
        return ans

    def getAction(self, car_dir, nd_from, nd_to):
        # TODO : get the car action
        # Tips : return an action and the next direction of the car if the nd_to is the Successor of nd_to
		# If not, print error message and return 0
        def dir_Action(A, B):
            if A == Direction(1):
                if B == Direction(1):   return Action(1)
                elif B == Direction(2): return Action(2)
                elif B == Direction(3): return Action(4)
                elif B == Direction(4): return Action(3)
            elif A == Direction(2):
                if B == Direction(1):   return Action(2)
                elif B == Direction(2): return Action(1)
                elif B == Direction(3): return Action(3)
                elif B == Direction(4): return Action(4)
            elif A == Direction(3):
                if B == Direction(1):   return Action(3)
                elif B == Direction(2): return Action(4)
                elif B == Direction(3): return Action(1)
                elif B == Direction(4): return Action(2)
            elif A == Direction(4):
                if B == Direction(1):   return Action(4)
                elif B == Direction(2): return Action(3)
                elif B == Direction(3): return Action(2)
                elif B == Direction(4): return Action(1)
            return -1
        
        next_dir = nd_from.getDirection(nd_to)
        return dir_Action(car_dir, next_dir)

    def getActions(self, nodes):
        # TODO : given a sequence of nodes, return the corresponding action sequence
        # Tips : iterate through the nodes and use getAction() in each iteration
        
        #extreme case
        if len(nodes) < 2: return -1

        #normal case
        current_dir = nodes[0].getDirection(nodes[1])
        ans = []
        for i in range(len(nodes) - 1):
            #print(self.getAction(current_dir, nodes[i], nodes[i+1]))
            ans.append(self.getAction(current_dir, nodes[i], nodes[i+1]))
            current_dir = nodes[i].getDirection(nodes[i+1])
        return ans

    def actions_to_str(self, actions):
        # cmds should be a string sequence like "fbrl....", use it as the input of BFS checklist #1
        cmd = "fbrls"
        cmds = ""
        print(actions)
        for action in actions: 
            #print(action)
            cmds += cmd[action-1]
        #print(cmds)
        return cmds

    def strategy(self, nd):
        return self.BFS(nd)

    def strategy_2(self, nd_from, nd_to):
        return self.BFS_2(nd_from, nd_to)
    
if __name__ == '__main__':
    #q = Maze("python/data/small_maze.csv")
    q = Maze("data/maze (5).csv")
    print(q.actions_to_str(q.getActions(q.BFS(1))))