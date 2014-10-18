// Copyright 2014 Gage Larsen
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//-----------------------------------------------------------
// CONSTANTS
//-----------------------------------------------------------
size_t MAXLENGTH = 256;


//-----------------------------------------------------------
// FUNCTION DECLARATIONS
//-----------------------------------------------------------
void printArgs(int, char**);
void readDirRec(const char* _dirName);
void PrintToString(long long _size);

//-----------------------------------------------------------
// MAIN
//-----------------------------------------------------------
int main(int argc, char** argv) {
  // printArgs(argc, argv);
  char* startDir;
  if ( argc == 1 ) {
    startDir =  ".";
  } else {
     startDir = *++argv;
  }

  struct stat statbuf;
  stat(startDir, &statbuf);
  PrintToString((long long)statbuf.st_size);
  printf(" %s\n", startDir);

  if ( startDir != NULL ) {
    readDirRec(startDir);
  } else {
    perror("Directory could not be openend\n");
  }
  return 0;
}

//-----------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------
void printArgs(int _argc, char** _argv) {
  while (--_argc) {
    printf("Arg: %s\n", *++_argv);
  }
  printf("All Done\n\n");
}

void PrintToString(long long _size) {
  int newSize = 0;
  char stringSize[MAXLENGTH];
  if ( _size > 100000 ) {
    newSize = _size / 1024;
    snprintf(stringSize, MAXLENGTH, "%dK", newSize);
  } else {
    newSize = _size;
    snprintf(stringSize, MAXLENGTH, "%d", newSize);
  }
  // snprintf(stringSize, MAXLENGTH, "%d", newSize);
  printf("%5s", stringSize);
}



void readDirRec(const char* _dirName) {
  DIR *curDir;
  struct stat statbuf;
  curDir = opendir(_dirName);
  // Check Directory is Opened
  if ( curDir == NULL ) {
    //  printf("Cannot open directory: %s\n", _dirName);
    exit(EXIT_FAILURE);
  }

  // Work with Directory
  struct dirent* item;
  const char* item_name;
  item = readdir(curDir);
  while ( item != NULL ) {
    if (strcmp(item->d_name, "..") != 0 && strcmp(item->d_name, ".") != 0) {
      char filename[MAXLENGTH];
      snprintf(filename, MAXLENGTH, "%s/%s", _dirName, item->d_name);
      stat(filename, &statbuf);
    } else {
      item = readdir(curDir);
      continue;
    }
    item_name = item->d_name;
    if ( item->d_type == DT_DIR ) {
      char newPath[MAXLENGTH];
      char* newSize;
      PrintToString((long long)statbuf.st_size);
      // printf("%5jd\n", (intmax_t)statbuf.st_size);
      printf(" %s/%s\n", _dirName, item_name);
      snprintf(newPath, MAXLENGTH, "%s/%s", _dirName, item_name);
      readDirRec(newPath);
    } else {
      char* newSize;
      PrintToString((long long)statbuf.st_size);
      // printf("%5jd\n", (intmax_t)statbuf.st_size);
      printf(" %s/%s\n", _dirName, item_name);
    }
    item = readdir(curDir);
  }
  if (closedir(curDir)) {
    printf("Could not Close: %s\n", _dirName);
    exit(EXIT_FAILURE);
  }
}
