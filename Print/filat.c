#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
struct stat atb;

void printFileType(){
  printf("File type \t\t: ");
  mode_t mode = atb.st_mode;

  if(S_ISBLK(mode) != 0)printf("Block Special File\n");
  else if(S_ISCHR(mode) != 0)printf("character special file\n");
  else if(S_ISDIR(mode) != 0)printf("directorie\n");
  else if(S_ISFIFO(mode) != 0)printf("Pipe and FIFO special file\n");
  else if(S_ISLNK(mode) != 0)printf("Symbolic link\n");
  else if(S_ISREG(mode) != 0)printf("regular file\n" );
  else printf("external link\n" );
}

void printAccesPriviliges() {
  printf("Access privileges \t: " );
  printf( (S_ISDIR(atb.st_mode)) ? "d" : "-");
  printf( (atb.st_mode & S_IRUSR) ? "r" : "-");
  printf( (atb.st_mode & S_IWUSR) ? "w" : "-");
  printf( (atb.st_mode & S_IXUSR) ? "x" : "-");
  printf( (atb.st_mode & S_IRGRP) ? "r" : "-");
  printf( (atb.st_mode & S_IWGRP) ? "w" : "-");
  printf( (atb.st_mode & S_IXGRP) ? "x" : "-");
  printf( (atb.st_mode & S_IROTH) ? "r" : "-");
  printf( (atb.st_mode & S_IWOTH) ? "w" : "-");
  printf( (atb.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n" );
}


int main(int argc, char const *argv[]) {
  if(argc != 2){
    printf("Error >>Not 2 arguments\n" );
    return 0;
  }
  int fd = lstat(argv[1], &attributes);
  printf("------------------- %s ------------------------\n",argv[1]);
  printFileType();
  printAccesPriviliges();
  printf("inode-Number \t\t: %d\n", atb.st_ino);
  printf("Device number \t\t: dev = %d rdev = %d\n",atb.st_rdev,atb.st_dev );
  printf("Links count \t\t: %d\n", atb.st_nlink);
  printf("UID \t\t\t: %d\n",atb.st_uid );
  printf("GID \t\t\t: %d\n", atb.st_gid);
  printf("File size \t\t: %d Bytes\n", atb.st_size);
  close(fd);
  return 0;
}
