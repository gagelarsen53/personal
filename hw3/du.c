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
char* convToString(int _size);

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
  printf("%5lld %s\n", (long long)statbuf.st_size, startDir);

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

char* convToString(int _size) {
  int newSize;
  char* stringSize;
  if ( _size > 100000 ) {
    newSize = _size / 1024;
    sprintf(stringSize, "%4dK", newSize);
  } else {
    newSize = _size;
    sprintf(stringSize, "%5d", newSize);
  }
  return stringSize;
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
      // printf("%5jd\n", (intmax_t)statbuf.st_size);
      printf("%5s %s/%s\n", convToString((int)statbuf.st_size), _dirName, item_name);
      snprintf(newPath, MAXLENGTH, "%s/%s", _dirName, item_name);
      readDirRec(newPath);
    } else {
      // printf("%5jd\n", (intmax_t)statbuf.st_size);
      printf("%5lld %s/%s\n", (long long)statbuf.st_size, _dirName, item_name);
    }
    item = readdir(curDir);
  }
  if (closedir(curDir)) {
    printf("Could not Close: %s\n", _dirName);
    exit(EXIT_FAILURE);
  }
}
