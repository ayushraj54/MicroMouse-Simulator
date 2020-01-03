#include "micromouseserver.h"

#include <thread> // both of these included for testing/debugging purposes
#include <chrono>

int rightcounter = 0; // used to check for end

int mazearr[20][20]; // setting all of the values automatically to 0
int xpos = 0; // coordinates
int ypos = 0;                   //both coords and direction being kept track of
int direction = 0; // direction

void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/


    mazearr[xpos][ypos] += 1; // adding 1 value to the current (x,y) position

    int originaldirection = direction; // using this to see where to turn after the next set of if statements

    int numwalls;
    numwalls = isWallRight() + isWallLeft() + isWallForward(); // using the number of walls to check if at an intersection

    //at an intersection
    if (numwalls < 2) {
        int lowest = 100; // find the direction that has been traversed the least
        if (direction == 0) { //up
            if (!isWallLeft()) { // checking if wall on left
                if (mazearr[xpos-1][ypos] < lowest) {
                    lowest = mazearr[xpos-1][ypos];
                    direction = 3;
                }
            }
            if (!isWallForward()) { // checking if wall in front
                if (mazearr[xpos][ypos+1] < lowest) {
                    lowest = mazearr[xpos][ypos+1];
                    direction = originaldirection;
                }
            }
            if (!isWallRight()) { // checking if wall on right
                if (mazearr[xpos+1][ypos] < lowest) {
                    lowest = mazearr[xpos+1][ypos];
                    direction = 1;
                }
            }
        } else if (direction == 1) { //right
            if (!isWallLeft()) { // checking if wall on left
                if (mazearr[xpos][ypos+1] < lowest) {
                    lowest = mazearr[xpos][ypos+1];
                    direction = 0;
                }
            }
            if (!isWallForward()) { // checking if wall in front
                if (mazearr[xpos+1][ypos] < lowest) {
                    lowest = mazearr[xpos+1][ypos];
                    direction = originaldirection;
                }
            }
            if (!isWallRight()) { // checking if wall on right
                if (mazearr[xpos][ypos-1] < lowest) {
                    lowest = mazearr[xpos][ypos-1];
                    direction = 2;
                }
            }
        } else if (direction == 2) { //down
            if (!isWallLeft()) { // checking if wall on left
                if (mazearr[xpos+1][ypos] < lowest) {
                    lowest = mazearr[xpos+1][ypos];
                    direction = 1;
                }
            }
            if (!isWallForward()) { // checking if wall in front
                if (mazearr[xpos][ypos-1] < lowest) {
                    lowest = mazearr[xpos][ypos-1];
                    direction = originaldirection;
                }
            }
            if (!isWallRight()) { // checking if wall on right
                if (mazearr[xpos-1][ypos] < lowest) {
                    lowest = mazearr[xpos-1][ypos];
                    direction = 3;
                }
            }
        } else if (direction == 3) { //left
            if (!isWallLeft()) { // checking if wall on left
                if (mazearr[xpos][ypos-1] < lowest) {
                    lowest = mazearr[xpos][ypos-1];
                    direction = 2;
                }
            }
            if (!isWallForward()) { // checking if wall in front
                if (mazearr[xpos-1][ypos] < lowest) {
                    lowest = mazearr[xpos-1][ypos];
                    direction = originaldirection;
                }
            }
            if (!isWallRight()) { // checking if wall on right
                if (mazearr[xpos][ypos+1] < lowest) {
                    lowest = mazearr[xpos][ypos+1];
                    direction = 0;
                }
            }
        }

        int changedirection = direction - originaldirection; // based on the changed direction, the mouse turns/moves in a certain direction

        if (changedirection < 0) { // not sure how to handle mod of negative numbers in c++
            //so, included the first half of the following if statement to always get a positive numbers
            changedirection = changedirection * -1;
            if (4 - (changedirection % 4) == 1){
                turnRight();
            } else if (4 - (changedirection % 4) == 3){
                turnLeft();
                rightcounter = 0;
            }
        } else { // if the changed direction is positive
            if ((changedirection % 4) == 1){
                turnRight();
            } else if ((changedirection % 4) == 3){
                turnLeft();
                rightcounter = 0;
            }
        }

    } else { // not at an intersection
        if (isWallForward() && isWallRight() && isWallLeft()) { //dead end
            turnLeft();
            turnLeft();
            if (direction == 3) {
                direction = 1;
            } else if (direction == 2) {
                direction = 0;
            } else {
                direction += 2;
            }
            rightcounter = 0; // setting right counter to 0 --> making sure it won't be counted for stopping condition
        } else if (isWallForward() && isWallLeft() && !isWallRight()) { //can only go right
            turnRight();
            rightcounter += 1; // incrementing rightcounter while turning right
            if (direction == 3) {
                direction = 0;
            } else {
                direction += 1;
            }
        } else if (isWallForward() && isWallRight() && !isWallLeft()) { //can only go left
            turnLeft();
            if (direction == 0) {
                direction = 3;
            } else {
                direction -= 1;
            }
            rightcounter = 0; // setting right counter to 0 --> making sure it won't be counted for stopping condition
        } else if (isWallLeft() && isWallRight() && !isWallForward()) {
            rightcounter = 0; // setting right counter to 0 --> making sure it won't be counted for stopping condition
        }
    }

    if (rightcounter >= 3) {
        foundFinish();
    }

    //changing the coordinates
    if (direction == 0) {
        ypos += 1;
    } else if (direction == 1) {
        xpos += 1;
    } else if (direction == 2) {
        ypos -= 1;
    } else if (direction == 3) {
        xpos -= 1;
    }

    moveForward();

}


