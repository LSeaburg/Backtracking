/* This program was created by Logan Seaburg
 * The references that I used were lecture notes and the
 * Stanford C++ Library guide on 106b.stanford.edu
 */

#include <iostream>
#include <string>
#include "letterinventory.h"
#include "set.h"
#include "strlib.h"
using namespace std;

int findAnagrams(LetterInventory& li, int max, Set<string>& dictionary, Vector<string>& choosenWords);

/* This function just validates input and passes the parameters to the real solver function
 * with the addition of an extra parameter so the program can keep track of what has already been selected.
 */
int findAnagrams(string phrase, int max, Set<string>& dictionary) {
    if (max < 0) {
        throw "max is invalid";
    }
    LetterInventory li = LetterInventory(phrase);
    Vector<string> choosenWords;
    return findAnagrams(li, max, dictionary, choosenWords);
}

/* Loops through all the words in the dictionary to find possible words that could be in the anagram
 * and adds them to chosen words, removing them from the letters that it is searching for.
 * This is repeated until there are no more letters, or the letters that do remain do not form a word.
 */
int findAnagrams(LetterInventory& li, int max, Set<string>& dictionary, Vector<string>& choosenWords) {
    int count = 0;
    for (string word : dictionary) {
        if (li.contains(word) ) {
            choosenWords.add(word);
            li.subtract(word);
            if (li.isEmpty()) {
                cout << choosenWords << endl;
                count ++;
            } else if (max != 1) {
                count += findAnagrams(li, max - 1, dictionary, choosenWords);
            }
            choosenWords.remove(choosenWords.size() - 1);
            li.add(word);
        }
    }
    return count;
}
