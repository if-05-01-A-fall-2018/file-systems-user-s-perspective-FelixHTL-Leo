#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define size 50

int main(int argc, char const *argv[]) {
  int cp_file, dest_file;
  char buffer[size];
  if(argc != 3) return 1;

  cp_file = open(argv[1], O_RDONLY);
  dest_file = open(argv[2], O_WRONLY);

  if (cp_file < 0) {
    printf("The file to copy doesn't exist\n");
    return 1;
  }

  if (dest_file < 0) {
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    dest_file = creat(argv[2], mode);
    open(argv[2], O_WRONLY);
    printf("File created\n");
  }

  int bytes;
  do {
    bytes = read(cp_file, buffer, size);
    write(dest_file, buffer, bytes);
  } while (bytes == size);
  printf("Writen\n");

  close(cp_file);
  close(dest_file);
  return 0;
}
