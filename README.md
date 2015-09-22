# Autonomous-Robot-AER201

This is the logic for team WAC's AER201 Robot. The robot is designed electromechanically and logically to compete in the a game outlined by the teaching staff of AER201 2015. Many decisions were made due to the inconsistencies of different gameboards (some had bumps, some lines were less detectable, etc.), resulting seemingly "poor" choices (such as the use of time delays for turning), but few alternatives. 

The rules were as follows:

1) There is a 1.8m x 3.2m game field as below (read as raw):

|===================||===================|

|........................................||........................................|

|........................................||........................................| 

|........................................||........................................|

|===================||===================|

Two teams (i.e. robots) will face off against each other. Each robot will be placed in one of the 1.8 x 1.6m half-fields.

2) Within each half-field is 22 ping pong balls. These 22 balls are split into 4 bunches of 4, 4, 7 and 7. The sets of 7 are randomly located within the middle, and changes each game. The sets of 4 are always at the outer corners of the field.

3) At the boundary of the two half-fields is a connect 4 game board. The robots must take the balls they collect, and play them into the connect 4 board. This version of connect four is NOT turn based, but instead uses a scoring system based on #of balls played, # of connect fours, and # of times robot got stuck.

4) The winner of the connect four game is the winner of the match. 

5) The robot cannot touch more than 1 ping pong ball at a time (i.e. you cannot move to 1 location, grab all the balls, and then play them all at the game board.

6) Teams are allowed to re-flash their arduino 1 minute before the start. Games last 7 minutes.
