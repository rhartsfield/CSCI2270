# CSCI2270
Final Project for Data Structures
Ryan Hartsfield

##########################
#     Project Summary    #
##########################
In this project, I have built a tic-tac-toe game from scratch. This includes two classes:
a) Board class which serves as the interface for the game itself
b) A ConfigTree class which is used for basic AI and keeping track of state of game

The main goal of the project was to gain practice using a search tree as a means for the computer to look for
the best possible move. Once the player makes the first move, the program populates the tree with all of the
paths that the game can take. Each path is cut off once a game-ending configuration is reached. Once the tree
is constructed, win probabilities are computed for each node (board configuration) of the tree. The computer
looks at this to determine which move to take. As the two players take turns, the board's configuration 
will move down the tree toward one of the leaves (a game-ending configuration). I have yet to take any AI courses, 
so all of this is improvised and results in a fairly dumb AI. This is because the program does not
look ahead to see if there are any losing paths, only a raw percentage of winning paths. Because the search
space is already quite small compared to a game like chess, it is not a problem to enumerate all possible paths. 
There are only 8! possible final configurations, and this is pruned greatly by the halting at winning configurations.

##########################
#       How to Run       #
##########################

Download the TicTacToe executable
Run the program from terminal using ./TicTacToe

##########################
#      Dependencies      #
##########################

N/A

##########################
#   System Requirements  #
##########################

Built for Linux. No external libraries are used.

##########################
#      Group Members     #
##########################

Ryan Hartsfield

##########################
#      Contributors      #
##########################



##########################
#   Open Issues / Bugs   #
##########################

-The AI currently does not look ahead to see if it will lose in the next n moves. It currently
assumes independence of configurations to make decisions. This leads to low quality decision
making.

-If stronger AI performance is implemented, should include difficulty levels based on how many
moves ahead are explored.

-Currently only single player. Designed this way so code would need to be refactored to allow for
a two-player experience.
