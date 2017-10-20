/* This program was created by Logan Seaburg.
 * I used lecture notes for reference.
 */

#include "Maze.h"

/* Tries to move up, then down, then left, then right
 * until it runs into a wall, a place it has already been,
 * or finds the exit.
 */
bool escapeMaze(Maze& maze, int row, int col) {
    if (! maze.inBounds(row, col)) {
        return true;
    } else if (! maze.isOpen(row, col)) {
        return false;
    } else {
        maze.mark(row, col);
        if (escapeMaze(maze, row + 1, col)) { //try up
            return true;
        }
        if (escapeMaze(maze, row - 1, col)) { //try down
            return true;
        }
        if (escapeMaze(maze, row, col - 1)) { //try left
            return true;
        }
        if (escapeMaze(maze, row, col + 1)) { //try right
            return true;
        }
        maze.unmark(row, col);
    }
    return false;
}
