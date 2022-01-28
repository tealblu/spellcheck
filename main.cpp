/*
 * Name: Charlie Hartsell
 * Date Submitted: 3/2/21
 * Lab Section: 004
 * Assignment Name: Lab 5
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
 int main()
 {
    // Declare the stringset and alternatives
    Stringset wordlist;
    string word;
    vector<string> alternatives;

    // Test code commented out as it is no longer needed
    // testStringset(wordlist);

    // Open file and add words to the stringset
    loadStringset(wordlist, "wordlist.txt");

    // Run the spell checker
    cout << "Enter the word to check: ";
    cin >> word;
    alternatives = spellcheck(wordlist, word);
     
    // Print the results
    cout << endl << "Alternatives are: ";
    for(int i = 0; i < alternatives.size(); i++) {
        cout << alternatives[i] << " ";
    }
    cout << endl;


    // End
    return 0;
 }
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 

 /**
  * Takes individual words from the input file and adds them to the hash table "words". Steps:
  * 1. Loop through the input file, adding words one at a time to the table using
  * the function Stringset::insert (e.g. words.insert(example))
  */
 void loadStringset(Stringset& words, string filename) {
    // Declare variables
    string tmp;

    // Open file
    fstream inFile;
    inFile.open(filename);

    // Add each line to the hash table
    while(getline(inFile, tmp)) {
        words.insert(tmp);
    }

    // Close the input file
    inFile.close();

    // Done!
 }

/**
 * Compares a given word with the dictionary and returns
 *  a vector of words that differ by one letter
 */
vector<string> spellcheck(const Stringset& words, string word)
{
    // Declare variables
    vector<string> alternatives;
    vector<list<string>> table = words.getTable();

    // Dictionary loop:
    // Begin by looping through the outer table
    for(int i = 0; i < table.size(); i++) {
        // Loop through the inner linked lists
        for(list<string>::const_iterator iterator = table[i].begin(); iterator != table[i].end(); iterator++) {
            // This string contains the current dictionary word
            string alt = *iterator;
            
            // Compare word sizes
            if(word.size() == alt.size()) {
                // Words are the same size, loop through word char by char
                int diff = 0;
                for(int j = 0; j < word.size(); j++) {
                    if(word[j] != alt[j]) {
                        diff++;
                    }
                }

                // If diff is EXACTLY ONE, add alt to alternatives
                if(diff==1) {
                    alternatives.push_back(alt);
                }
            }
        }
    }

    // Return the vector of results
    return alternatives;
}