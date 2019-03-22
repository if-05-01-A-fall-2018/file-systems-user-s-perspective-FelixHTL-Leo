#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char const *argv[]) {
    DIR *dir = opendir(".");

    struct dirent *dre;
    if (dir == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }

    while ((dre = readdir(dir)) != NULL) {
      struct stat file;
        if(stat(dre->d_name, &file) < 0) return 1;


      printf("\n");
      if(S_ISBLK(file.st_mode)) printf("b");
      else if (S_ISREG(file.st_mode)) printf("-");
      else if (S_ISDIR(file.st_mode)) printf("d");
      else if (S_ISCHR(file.st_mode)) printf("c");
      else if (S_ISLNK(file.st_mode)) printf("l");

      if (file.st_mode & S_IRUSR)printf("r");
      else printf("-");

      if (file.st_mode & S_IWUSR)printf("w");
      else printf("-");

      if (file.st_mode & S_IXUSR)printf("x");
      else printf("-");

      if (file.st_mode & S_IRGRP)printf("r");
      else printf("-");

      if (file.st_mode & S_IWGRP)printf("w");
      else printf("-");

      if (file.st_mode & S_IXGRP)printf("x");
      else printf("-");

      if (file.st_mode & S_IROTH)printf("r");
      else printf("-");

      if (file.st_mode & S_IWOTH)printf("w");
      else printf("-");

      if (file.st_mode & S_IXOTH)printf("x ");
      else printf("- ");

      printf("%d ",file.st_uid);
      printf("%d ",file.st_gid);
      printf("%ld \t",file.st_size);

      char date[18];
      strftime(date, 18, "%Y-%m-%d-%H-%M", localtime(&file.st_mtime));
      printf("%s ",date);
      printf("%s",dre->d_name );

  }
        closedir(dir);
  return 0;
}
