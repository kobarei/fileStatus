#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int c_fd;
struct stat info;

void copycat(char const *file) {
  char str[256];
  int size, f_fd;

  // while there are unread characters left,
  // read and write to concat.txt
  f_fd = open(file, O_RDONLY);
  fstat(f_fd, &info);
  if (f_fd >= 0 && (info.st_mode & S_IFREG)) {
    printf("copying %s...\n", file);
    while((size = read(f_fd, str, sizeof(str))) > 0){
      write(c_fd, str, size);
    }
  } else {
    printf("Error occured. check: %s\n", file);
  }
  close(f_fd);
}

int main(int argc, char const *argv[]) {
  int i;

  // open concat.txt
  // if can't find the file, create one
  c_fd = open("concat.txt", O_WRONLY);
  if (c_fd < 0) {
    creat("concat.txt", 0644);
    c_fd = open("concat.txt", O_WRONLY);
  }

  // copy paste for each files
  for (i = 1; i < argc; ++i){
    copycat(argv[i]);
  }

  close(c_fd);
  return 0;
}