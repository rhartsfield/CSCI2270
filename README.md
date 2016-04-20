# CSCI2270
Final Project for Data Structures
Ryan Hartsfield

In this project, I will be building a tic-tac-toe game from scratch. This will include at least two classes:
a) Board class which will serve as the game itself
b) A ConfigTree class which will be used for the creation of a computer AI
The main goal of the project is to gain practice using a search tree as a means for the computer to look for
the best possible move. Once the player makes the first move, the program will populate the tree all of the
paths that the game can take. As the two players take turns, the board's configuration will move down the tree 
toward one of the leaves. I have not taken any AI courses, so I will be improvising all of this. Because the search
space is already quite small compared to chess (only 8! if we leave out first move, but over 100k paths to these 8!), it should not be a problem to 
enumerate all possible paths. Down each of the initial n <= 8 paths, the program will count how many end in a winning
configuration for the computer and calculate a probability from that. It will then choose the move with the highest win
probability. 