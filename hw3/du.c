#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//-----------------------------------------------------------
// CONSTANTS
//-----------------------------------------------------------
size_t MAXLENGTH=256;


//-----------------------------------------------------------
// FUNCTION DECLARATIONS
//-----------------------------------------------------------
void printArgs(int, char**);
void readDirRec(const char* _dirName);
void readDirHelp(const char* _dirName);

//-----------------------------------------------------------
// MAIN
//-----------------------------------------------------------
int main(int argc, char** argv)
{
  printArgs(argc, argv);

  if( argc == 1 ){
    printf("No Args\n");
    char cwd[MAXLENGTH];
    if( getcwd(cwd, MAXLENGTH) != NULL ){
      printf("Current Working Directory: %s\n", cwd);
    }else{
      perror("getcwd error");
    }

    //char* startDir = cwd;
    char* startDir = ".";
    if( startDir != NULL ){
      printf("Directory Opened\n");
      readDirRec(startDir);
    }else{
      perror("Directory could not be openend\n");
    }

  }else{
    printf("Args\n");
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
}

void readDirRec(const char* _dirName){
  DIR *curDir;
  curDir = opendir(_dirName);

  //Check Directory is Opened
  if( curDir == NULL ){
    printf("Cannot open directory: %s\n", _dirName);
    exit(EXIT_FAILURE);
  }

  //Work with Directory
  struct dirent* item;
  const char* item_name;
  while(1){
    item = readdir(curDir);
    if( item == NULL ){
      break;
    }
    item_name = item->d_name;
    if( item->d_type == DT_DIR ){
      if(strcmp(item_name, "..") != 0 && strcmp(item_name, ".") != 0){
        printf("%s\n", item_name);
        char newPath[MAXLENGTH];
        snprintf(newPath, MAXLENGTH, "%s", item_name);
        readDirHelp(newPath);
      }
    }else{
      printf("%s\n", item_name);
    }
  }
  if(closedir(curDir)){
    printf("Could not Close: %s\n", _dirName);
    exit(EXIT_FAILURE);
  }

}

void readDirHelp(const char* _dirName){
  DIR *curDir;
  curDir = opendir(_dirName);

  //Check Directory is Opened
  if( curDir == NULL ){
    printf("Cannot open directory: %s\n", _dirName);
    exit(EXIT_FAILURE);
  }

  //Work with Directory
  struct dirent* item;
  const char* item_name;
  while(1){
    item = readdir(curDir);
    if( item == NULL ){
      break;
    }
    item_name = item->d_name;
    if( item->d_type == DT_DIR ){
      if(strcmp(item_name, "..") != 0 && strcmp(item_name, ".") != 0){
        printf("%s/%s\n", _dirName, item_name);
        char newPath[MAXLENGTH];
        snprintf(newPath, MAXLENGTH, "%s/%s", _dirName, item_name);
        readDirHelp(newPath);
      }
    }else{
      printf("%s/%s\n", _dirName, item_name);
    }
  }
  if(closedir(curDir)){
    printf("Could not Close: %s\n", _dirName);
    exit(EXIT_FAILURE);
  }
}
