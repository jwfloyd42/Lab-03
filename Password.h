#if !defined PASSWORD_H
#define PASSWORD_H

#include "CSC2110/ListArrayIterator.h"
#include "CSC2110/Permutation.h"
#include "CSC2110/ReadFile.h"
#include "CSC2110/Random.h"
#include "CSC2110/Integer.h"
#include "CSC2110/Double.h"
#include "CSC2110/ListArray.h"
#include "CSC2110/Text.h"
#include "CSC2110/HighPerformanceCounter.h"
#include "CSC2110/Keyboard.h"
#include "CSC2110/Matrix.h"
#include "CSC2110/Poly.h"
#include "CSC2110/WriteFile.h"
#include "CSC2110/Random.h"
#include <iostream>


class Password
{
   private:
      ListArray<String>* viable_words;  //the list of words that can still be the password
      ListArray<String>* all_words;  //the original list of words
      int len;  //the length of the first word entered is stored to check that all subsequent words have the same length

      //a private helper method to report the number of character matches between two Strings
      int getNumMatches(String* curr_word, String* word_guess);

   public:
		Password();
		~Password();
		void addWord(String* wrd);
		void guess(int try_password, int num_matches);
		int getNumberOfPasswordsLeft();
		void displayViableWords();
		int bestGuess();
		String* getOriginalWord(int index);


};

#endif
