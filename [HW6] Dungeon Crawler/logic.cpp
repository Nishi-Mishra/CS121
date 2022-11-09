#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
  
    bool debug = 0;
    //int rowCols[4]; // int row; col; playRow; playCol;
    string map_size; 
    char currChar;
    bool hasWayOut = false;

    char** map; 
\
    ifstream file(fileName); 

    // check is file open 
    if (file.is_open()) {
        /*
        for (int i = 0; i < 4; i++) {
            rowCols[i] = 0; 
            file >> map_size; 
            for (size_t j = 0; j < map_size.size(); j++) {
                currChar = map_size.at(j); 
                if (isdigit(currChar)) {
                    rowCols[i] *= 10; 
                    rowCols[i] += (currChar - '0');
                    if (debug) cout << "We put " << rowCols[i] << " into array " << endl;
                }
                else
                    return nullptr;
            }
            
        }*/

        try {
            file >> maxRow;
            file >> maxCol;

            if ((INT32_MAX * 1.0 / maxRow) < maxRow)
                return nullptr;
            if ((INT32_MAX * 1.0 / maxCol) < maxCol)
                return nullptr;

            file >> player.row;
            file >> player.col;
        }
        catch (...) {
            return nullptr; 
        }
        

        // see if the first 4 characters are numbers 
        // check is the player in a possible place within the grid -- quit if not 
        /*maxRow = rowCols[0];
        maxCol = rowCols[1];*/

        if (player.row >= maxRow || player.row < 0)
            return nullptr;

        if (player.col >= maxCol || player.col < 0)
            return nullptr;

        // call the create map function & catch the new map 
        map = createMap(maxRow, maxCol);
        if (map == nullptr)
            return nullptr; 

        for (int r = 0; r < maxRow; r++) {
            for (int c = 0; c < maxCol; c++) {

                file >> currChar;

                if (currChar == TILE_OPEN || currChar == TILE_PILLAR || currChar == TILE_AMULET || currChar == TILE_MONSTER || currChar == TILE_TREASURE) {
                    map[r][c] = currChar;
                    if (debug) cout << "[" << r << "]" << "[" << c << "] " << "Has valid character : " << currChar << endl;
                }
                else if (currChar == TILE_DOOR || currChar == TILE_EXIT) {
                    map[r][c] = currChar;
                    hasWayOut = true;
                    if (debug) cout << "Has way out " << endl;
                }
                else if (currChar == TILE_PLAYER) {
                    map[r][c] = currChar;
                    deleteMap(map, maxRow);
                    return nullptr; // can't have a playa 
                }
                else {
                    if (debug) cout << "[" << r << "]" << "[" << c << "] " << "Has invalid character: " << currChar << endl;
                    deleteMap(map, maxRow);
                    return nullptr; // any other invalid character 
                }
            }// end of inner for loop
        } // end outer for loop 



        if (file >> currChar) {
            if (debug) cout << "Current char : " << currChar << " not end of file" << endl;
            deleteMap(map, maxRow);
            return nullptr; // there is still more to go 
        }

        if (!hasWayOut) {
            deleteMap(map, maxRow);
            return nullptr; // no exit 
        }

        map[player.row][player.col] = TILE_PLAYER; // does the player placement require any checks ? 



        // if the map is not tile open for player location abort load 
        /*if (map[player.row][player.col] == TILE_OPEN) {
            map[player.row][player.col] = TILE_PLAYER;
        }
        else if (map[player.row][player.col] == TILE_TREASURE) {
            map[player.row][player.col] = TILE_PLAYER; 
        }
        else {
            if (debug) cout << "Player location is not open \n" << endl;
            deleteMap(map, maxRow); 
            return nullptr;
        }*/

    } // end file open if block 
    else {
        return nullptr;
    }

    // place character after checking if that tile is not open 


    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    input = (char) tolower(input); 

    if (nextRow < 0 || nextCol < 0)
        return; 

    if (input == INPUT_STAY)
        return; 
    else if (input == MOVE_UP) {
        nextRow -= 1; 
        return; 
    }
    else if (input == MOVE_DOWN) {
        nextRow += 1; 
        return;
    }
    else if (input == MOVE_LEFT) {
        nextCol -= 1;
        return; 
    }
    else if (input == MOVE_RIGHT) {
        nextCol += 1;
        return; 
    }
    else {
        return; 
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {

    //allocate whatever memory and init all the tiles to '-'

    if (maxRow <= 0 || maxCol <= 0)
        return nullptr; 

    char** map = new char* [maxRow]; 
    for (int r = 0; r < maxRow; r++) {
        map[r] = new char[maxCol]; 
    }

    for (int r = 0; r < maxRow; r++) {
        for (int c = 0; c < maxCol; c++) {
            map[r][c] = '-'; 
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {

    if (map == nullptr) {
        maxRow = 0; 
        return;
    }

    for (int r = 0; r < maxRow; r++)
        delete[] map[r]; 
    delete [] map;

    maxRow = 0; 
    map = nullptr; 
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    

    // check if row * col > int max 
    char** BIG_map; 

    if (map == nullptr) {
        /*maxRow = 0;
        maxCol = 0; */
        return nullptr;
    }

    if ((INT32_MAX * 1.0 / maxRow) < maxRow) 
        return nullptr;
    if ((INT32_MAX * 1.0 / maxCol) < maxCol)
        return nullptr;

    if (maxRow <= 0)
        return nullptr; 
    if (maxCol <= 0)
        return nullptr; 

    bool debug = 0;
    int newRow = maxRow * 2;
    int newCol = maxCol * 2;

    if ((INT32_MAX * 1.0 / newRow) < newRow) 
        return nullptr;
    if ((INT32_MAX * 1.0 / newCol) < newCol)
        return nullptr;

    BIG_map = createMap(newRow, newCol);

    /*for (int r = 0; r < maxRow; r++) {
        for (int c = 0; c < maxCol; c++) {
            cout << map[r][c] << " ";
        }
        cout << endl;
    }*/

    // spot the player and pluck it out because we don't wanna deal with it 
    int playRow = -1; int playCol = -1;
    for (int r = 0; r < maxRow; r++) {
        for (int c = 0; c < maxCol; c++) {
            if (map[r][c] == TILE_PLAYER) {
                playRow = r;
                playCol = c;
                map[r][c] = TILE_OPEN;
                break;
            }
        }
    }

    // double the board left to right first 
    if (debug) cout << endl;
    for (int r = 0; r < maxRow; r++) {
        for (int i = 0; i < 2; i++) {
            for (int c = 0; c < maxCol; c++) {
                // cout << "In the innermost for loop i: " << i  << "  r: " << r << "  c: " << c << endl;
                if (i == 0) {
                    BIG_map[r][c] = map[r][c];
                    if (debug) cout << BIG_map[r][c] << " ";
                }
                else if (i == 1) {
                    BIG_map[r][c + maxCol] = map[r][c];
                    if (debug) cout << BIG_map[r][c + maxCol] << " ";
                }
            }
        }
        if (debug) cout << endl;
    }

    // copy the top half to the bottom half 
    for (int r = 0; r < maxRow; r++) {
        for (int c = 0; c < newCol; c++) {
            BIG_map[r + maxRow][c] = BIG_map[r][c];
            if (debug) cout << BIG_map[r + maxRow][c] << " ";

        }
        if (debug) cout << endl;
    }

    if (playRow != -1 && playCol != -1) {
        // cout << "In the player put back if statement " << playRow << playCol << BIG_map[playRow][playCol] << " : " << TILE_PLAYER << endl;
        BIG_map[playRow][playCol] = TILE_PLAYER; // player is placed back in the game 
    }

    /*cout << endl;
    for (int r = 0; r < newRow; r++) {
        for (int c = 0; c < newCol; c++) {
            if (debug) cout << BIG_map[r][c] << " ";
        }
        if (debug) cout << endl;
    }*/

    // delete the old map 
    deleteMap(map, maxRow);

    // afterword reassign value of maxRow / maxCol 
    maxRow = newRow;
    maxCol = newCol;

    return BIG_map;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure.
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {

    //STATUS_STAY = 0;      // flag indicating player has stayed still
    //STATUS_MOVE = 1;      // flag indicating player has moved in a direction
    //STATUS_TREASURE = 2;      // flag indicating player has stepped onto the treasure
    //STATUS_AMULET = 3;      // flag indicating player has stepped onto an amulet
    //STATUS_LEAVE = 4;      // flag indicating player has left the current room -- door 
    //STATUS_ESCAPE = 5;      // flag indicating player has gone through the dungeon exit

    bool debug = 0; 

    if (nextRow == maxRow || nextCol == maxCol || nextRow < 0 || nextCol < 0) {
        nextRow = player.row;
        nextCol = player.col; 
        return STATUS_STAY;
    }
    else if (nextRow < maxRow && nextRow >= 0 && nextCol < maxCol && nextCol >= 0) {
        // normal case 
        if (map[nextRow][nextCol] == TILE_OPEN) {
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol; 
            map[nextRow][nextCol] = TILE_PLAYER; 
            return STATUS_MOVE;
        }
        else if (map[nextRow][nextCol] == TILE_TREASURE) {
            map[player.row][player.col] = TILE_OPEN; 
            map[nextRow][nextCol] = TILE_PLAYER; 
            player.row = nextRow;
            player.col = nextCol;
            player.treasure += 1;
            return STATUS_TREASURE;
        }
        else if (map[nextRow][nextCol] == TILE_AMULET) {

            if(debug) cout << "Here in the amulet trigger" << endl; 
            map[player.row][player.col] = TILE_OPEN;
            map[nextRow][nextCol] = TILE_PLAYER;
            player.row = nextRow; 
            player.col = nextCol; 
            return STATUS_AMULET;
        }
        else if (map[nextRow][nextCol] == TILE_DOOR) {
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;
            map[player.row][player.col] = TILE_PLAYER;
            return STATUS_LEAVE;
        }
        else if (map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR) {
            nextRow = player.row;
            nextCol = player.col;
            return STATUS_STAY;
        }
        else if (map[nextRow][nextCol] == TILE_EXIT) {
            if (player.treasure > 0) {
                map[player.row][player.col] = TILE_OPEN; 
                player.row = nextRow;
                player.col = nextCol;
                map[player.row][player.col] = TILE_PLAYER;
                return STATUS_ESCAPE;
            }
            else {
                nextRow = player.row;
                nextCol = player.col;
                return STATUS_STAY;
            }      
        }
        else {
            nextRow = player.row;
            nextCol = player.col;
            return STATUS_STAY;
        }
    }
    else {
        nextRow = player.row;
        nextCol = player.col;
        return STATUS_STAY;
    }
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {

    // check in a 4 for loops left right up down until potentially a monster 

    bool death = false; 

    // go up 
    for (int r = player.row-1; r >= 0; r--) {
        if (map[r][player.col] == TILE_PILLAR) { // can't see thru pillars 
            break;
        }
        else if (map[r][player.col] == TILE_MONSTER) {
            
            if (map[r + 1][player.col] == TILE_PLAYER) { // if the tile down one has a playa then update map and say death has occured 
                map[r + 1][player.col] = TILE_MONSTER; 
                map[r][player.col] = TILE_OPEN;
                death = true; 
            } else { // now if the monster is found, it will eat through literally anything in front of it 
                map[r + 1][player.col] = TILE_MONSTER;
                map[r][player.col] = TILE_OPEN; 
            }
        }
    }

    // go down 
    for (int r = player.row+1; r < maxRow; r++) {
        if (map[r][player.col] == TILE_PILLAR) { // can't see thru pillars 
            break;
        }
        else if (map[r][player.col] == TILE_MONSTER) {
            if (map[r - 1][player.col] == TILE_PLAYER) { // if the tile up one has a playa then update map and return 
                map[r - 1][player.col] = TILE_MONSTER;
                map[r][player.col] = TILE_OPEN;
                death = true;
            }
            else { // now if the monster is found, it will eat through literally anything in front of it 
                map[r - 1][player.col] = TILE_MONSTER;
                map[r][player.col] = TILE_OPEN;
            }
        }
    }

    // go left 
    for (int c = player.col-1; c >= 0; c--) {
        if (map[player.row][c] == TILE_PILLAR) { // can't see thru pillars 
            break;
        }
        else if (map[player.row][c] == TILE_MONSTER) {
            if (map[player.row][c + 1] == TILE_PLAYER) { // if the tile right one has a playa then update map and return 
                map[player.row][c + 1] = TILE_MONSTER;
                map[player.row][c] = TILE_OPEN;
                death = true;
            }
            else { // now if the monster is found, it will eat through literally anything in front of it 
                map[player.row][c + 1] = TILE_MONSTER;
                map[player.row][c] = TILE_OPEN;
            }
        }
    }

    // go right 
    for (int c = player.col+1; c < maxCol; c++) {
        if (map[player.row][c] == TILE_PILLAR) { // can't see thru pillars 
            break;
        }
        else if (map[player.row][c] == TILE_MONSTER) {
            if (map[player.row][c - 1] == TILE_PLAYER) { // if the tile left one has a playa then update map and return 
                map[player.row][c - 1] = TILE_MONSTER;
                map[player.row][c] = TILE_OPEN;
                death = true;
            }
            else { // now if the monster is found, it will eat through literally anything in front of it 
                map[player.row][c - 1] = TILE_MONSTER;
                map[player.row][c] = TILE_OPEN;
            }
        }
    }

    return death;
}
