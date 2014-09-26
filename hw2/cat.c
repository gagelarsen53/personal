#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------
// CONSTANTS
//-----------------------------------------------------------
int MAXLENGTH=256;

//-----------------------------------------------------------
// FUNCTION DECLARATIONS
//-----------------------------------------------------------
void printArgs(int, char**);
void printStdIn(int _writeLine);
void printFile(FILE* _input, int _writeLine);

//-----------------------------------------------------------
// MAIN
//-----------------------------------------------------------
int main(int argc, char** argv)
{
  int useLineNum = 0;
  if( argc == 2 ){
    if( strcmp( argv[1], "-\?") == 0 ){
      printf("Usage: ./cat [-n\?] [file ...]\n");
      exit(0);
    }
    if( strcmp( argv[1], "-n" ) == 0){
      useLineNum = 1;
    }
    else{
      FILE* ifp;
      char* mode = "r";
      ifp = fopen(argv[2], mode);
      if( ifp == NULL ){
        printf("cat: %s: No such file or Direcotry\n", argv[1]);
        exit(1);
      }
    }
    printStdIn(useLineNum);
  }else{
    printStdIn(useLineNum);
  }
}

//-----------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------
void printArgs(int _argc, char** _argv){
  while (--_argc){
    printf("Arg: %s\n", *++_argv);
  }
  printf("All Done\n");
  exit(0);
}

void printStdIn(int _printLine){
  char line[MAXLENGTH];
  int lineNum = 0;
  while( fgets(line, MAXLENGTH, stdin) != NULL ){
    if( _printLine ){
      lineNum++;
      printf("     %d  %s", lineNum, line);
    }else{
      printf("%s", line);
    }
  }
}

void printFile(FILE* _input, int _writeLine){

}
