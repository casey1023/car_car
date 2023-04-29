import maze as mz
from score import ScoreboardFake, Scoreboard
from BTinterface import BTinterface

import numpy as np
import pandas
import time
import sys
import os

def main():
    
    maze = mz.Maze("python/data/medium_maze.csv")
    command = maze.actions_to_str(maze.getActions(maze.strategy()))
    print(command)
    interf = BTinterface()

    point = Scoreboard("qwq", "http://140.112.175.18:3000")
    #point = ScoreboardFake("qwq", "python/data/fakeUID.csv")

    # TODO : Initialize necessary variables
    
    if (sys.argv[1] == '0'):
        print("Mode 0: for treasure-hunting")
        # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible
        interf.start()
        interf.send_action(command+"e")

        while True:
            UID_temp = []
            UID = interf.get_UID()
            #msg = interf.ser.SerialReadString()
            if UID != 0:
                if len(UID) != 10:
                    print(UID)
                    UID_temp.append(UID)

                    count = 0
                    for i in UID_temp:
                        count += len(i)

                    if count == 10:
                        new_UID = ""
                        for i in UID_temp:
                            new_UID += i
                        print(new_UID)
                        point.add_UID(new_UID[2:])
                        print(point.getCurrentScore())
                        UID_temp = []
                else:
                    print(UID)
                    point.add_UID(UID[2:])
                    print(point.getCurrentScore())
            #if msg != "":
            #    print("msg:" + msg)
        
    elif (sys.argv[1] == '1'):
        print("Mode 1: Self-testing mode.")
        # TODO: You can write your code to test specific function.

        #command = maze.actions_to_str(maze.getActions(maze.BFS(1)))
        command = input("input here :")
        interf.start()
        interf.send_action(command)

        while True:
            UID = interf.get_UID()
            if UID != 0:
                print(UID)
                point.add_UID(UID[2:])
                print(point.getCurrentScore())
        
        interf.end_process()


    

if __name__ == '__main__':
    main()
