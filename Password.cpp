#include "Password.h"
#include <iostream>

using CSC2110::ListArrayIterator;
using namespace std;

Password::Password()
{
    viable_words = new ListArray<String>();
    all_words = new ListArray<String>();
    len = 0;
}
Password::~Password()
{
    int allSize = all_words->size();
    int possible_size = viable_words->size();
    for(int i = 1; i <= allSize; i++)
        all_words->remove(i);
    for(int i = 1; i <= possible_size; i++)
        viable_words->remove(i);

    delete all_words;
    delete viable_words;

}
void Password::addWord(String* wrd)
{
    if (all_words->size() == 0)
    {
        all_words->add(wrd);
        viable_words->add(wrd);
        len = wrd->length();
    }
    else if(len == wrd->length())
    {
        all_words->add(wrd);
        viable_words->add(wrd);
    }

}

void Password::guess(int try_password, int num_matches)
{
    ListArrayIterator<String>* iter = viable_words->iterator();
    ListArray<String>* new_viable_words = new ListArray<String>;
    String* guess_word=all_words->get(try_password);

    while(iter->hasNext())
    {
        String* viable = iter->next();
        if(num_matches == getNumMatches(guess_word, viable))
        {
            new_viable_words->add(viable);
        }
    }
    delete viable_words;
    viable_words = new_viable_words;

}
int Password::getNumberOfPasswordsLeft()
{
    return viable_words->size();
}
void Password::displayViableWords()
{
    ListArrayIterator<String>* iter = viable_words->iterator();
    String* display_word;
    while(iter->hasNext())
    {
        display_word = iter->next();
        display_word->displayString();
        cout << endl;
    }


}
String* Password::getOriginalWord(int index)
{
    return all_words->get(index);
}
int Password::getNumMatches(String* current, String* guess)
{
    int strLen = current->length();
    int num_matches = 0;

    for(int i = 0; i < strLen; i++)
    {
        if(guess->charAt(i) == current->charAt(i))
            num_matches++;
    }
    return num_matches;
}

int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int current_num_matches = count_num_matches[j];
         if (current_num_matches > most_num_matches)
         {
            most_num_matches = current_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the currentent word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}
