/* This program was written by Logan Seaburg.
 * I used lecture notes and reference guides on the website.
 */

#include <string>
#include "boggle.h"
#include "grid.h"
#include "lexicon.h"
#include "strlib.h"
using namespace std;

bool humanWordSearchHelper(Grid<char>& board, string word, int row, int col);
void computerWordSearchHelper(Grid<char>& board, Lexicon& dictionary, Set<string>& allWords, string word, int row, int col);

/* This function validates input and searches the entire board for
 * the first letter. When it finds the first letter it passes that location
 * and the rest of the word to the recursive part of the function.
 */
bool humanWordSearch(Grid<char>& board, string word) {
    if (word.length() < MIN_WORD_LENGTH) {
        return false;
    }
    word = toUpperCase(word);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == word[0]) {
                board[r][c] = ' ';
                if (humanWordSearchHelper(board, word.substr(1), r, c)) {
                    board[r][c] = word[0];
                    return true;
                }
                board[r][c] = word[0];
            }
        }
    }
    return false;
}

/* Searches all the spots around the given square for the next letter in the word.
 * It continues this until the entire word is found. At each step of the way it places
 * a space instead of the char to avoid counting the same square twice.
 */
bool humanWordSearchHelper(Grid<char>& board, string word, int row, int col) {
    for (int r = -1; r < 2; r++) {
        for (int c = -1; c < 2; c++) {
            if (board.inBounds(row + r, col + c)) {
                if (board[row + r][col + c] == word[0]) {
                    if (word.length() == 1) {
                        return true;
                    }
                    board[row + r][col + c] = ' ';
                    if (humanWordSearchHelper(board, word.substr(1), row + r, col + c)) {
                        board[row + r][col + c] = word[0];
                        return true;
                    }
                    board[row + r][col + c] = word[0];
                }
            }
        }
    }
    return false;
}

/* Passes every square location and content to the to the recursive part of the function.
 * Sets that square to a space to avoid counting that square twice.
 */
Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary) {
    Set<string> allWords;
    string word = "";
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            word += board[r][c];
            board[r][c] = ' ';
            computerWordSearchHelper(board, dictionary, allWords, word, r, c);
            board[r][c] = word[0];
            word = "";
        }
    }
    return allWords;
}

/* Tries every square around the the given square until a word
 * is found or until the program sees that there is no word with that
 * given start.
 */
void computerWordSearchHelper(Grid<char>& board, Lexicon& dictionary, Set<string>& allWords, string word, int row, int col) {
    for (int r = -1; r < 2; r++) {
        for (int c = -1; c < 2; c++) { //looks at all the adjcent letters
            if (board.inBounds(row + r, col + c)) {
                word += board[row + r][col + c];
                board[row + r][col + c] = ' ';
                if (word.length() >= 4 && dictionary.contains(word)) {
                    allWords.add(word);
                }
                if (dictionary.containsPrefix(word)) {
                    computerWordSearchHelper(board, dictionary, allWords, word, row + r, col + c);
                }
                board[row + r][col + c] = word[word.length() - 1];
                word = word.substr(0, word.length() - 1);
            }
        }
    }
    return;
}
