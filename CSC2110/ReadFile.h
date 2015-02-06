#if !defined READ_FILE_H
#define READ_FILE_H

#include "Text.h"
using namespace CSC2110;

#include <fstream>

class ReadFile
{
   private:
      std::ifstream* input_file;
      bool _eof;
      bool closed;

   public:
      ReadFile(const char* file_name);
      ~ReadFile();
      String* readLine();
      bool eof();
      void close();
};

#endif
