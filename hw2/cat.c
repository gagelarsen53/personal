#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------
// CONSTANTS
//-----------------------------------------------------------
int MAXLENGTH=256;
char* MODE="r";

//-----------------------------------------------------------
// FUNCTION DECLARATIONS
//-----------------------------------------------------------
void printArgs(int, char**);
void printStdIn(int _writeLine);
void printFile(FILE* _input, int _writeLine, int* _curLineNum);

//-----------------------------------------------------------
// MAIN
//-----------------------------------------------------------
int main(int argc, char** argv)
{
  //printArgs(argc, argv);
  int useLineNum = 0;
  int argIndex = 0;
  int lineNum = 0;
  int* curLineNum = &lineNum;
  if( argc >= 2 ){
    if( strcmp( argv[1], "-\?") == 0 ){
      printf("Usage: ./cat [-n\?] [file ...]\n");
      exit(0);
    }
    if( strcmp( argv[1], "-n" ) == 0){
      useLineNum = 1;
      argIndex++;
    }
    if(argIndex + 1 < argc){
      while(argIndex + 1 < argc){
        argIndex++;
        FILE* ipf = fopen(argv[argIndex], MODE);
        if(ipf != NULL){
          printFile(ipf, useLineNum, curLineNum);
        }else{
          printf("%s: %s: No such file or Directory\n", argv[0], argv[argIndex]);
          exit(1);
        }
      }
      exit(0);
    }
    else{
      printStdIn(useLineNum);
    }
  }else{
    printStdIn(useLineNum);
  }
  return 0;
}

//-----------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------
void printArgs(int _argc, char** _argv){
  while (--_argc){
    printf("Arg: %s\n", *++_argv);
  }
  printf("All Done\n");
  //exit(0);
}

void printStdIn(int _printLine){
  char line[MAXLENGTH];
  int lineNum = 0;
  while( fgets(line, MAXLENGTH, stdin) != NULL ){
    if( _printLine ){
      lineNum++;
      printf("%6d\t%s", lineNum, line);
    }else{
      printf("%s", line);
    }
  }
}

void printFile(FILE* _input, int _writeLine, int* _curLineNum){
  char line[MAXLENGTH];
  while( fgets(line, MAXLENGTH, _input) != NULL ){
    if( _writeLine ){
      (*_curLineNum)++;
      printf("%6d\t%s", (*_curLineNum), line);
    }else{
      printf("%s", line);
    }
  }
}
