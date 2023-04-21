import maze as mz
from score import ScoreboardFake, Scoreboard
from BTinterface import BTinterface

import numpy as np
import pandas
import time
import sys
import os

def main():
    maze = mz.Maze("data/small_maze.csv")
    #point = Scoreboard("your team name", "ask TA for ip")
    point = ScoreboardFake("your team name", "data/fakeUID.csv")
    interf = BTinterface()
    # TODO : Initialize necessary variables
    
    if (sys.argv[1] == '0'):
        print("Mode 0: for treasure-hunting")
        # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible
        
    elif (sys.argv[1] == '1'):
        print("Mode 1: Self-testing mode.")
        # TODO: You can write your code to test specific function.

        command = maze.actions_to_str(maze.getActions(maze.BFS(1)))
        interf.start()
        interf.send_action(command)
        interf.end_process()

        while True:
            UID = interf.get_UID()
            if UID != 0:
                print(UID)
                point.add_UID(UID)
                print(point.getCurrentScore())


    

if __name__ == '__main__':
    main()
