#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

struct stat info;

// detect file type
void print_file_type(void) {
  printf("File Type:    ");
  switch (info.st_mode & S_IFMT) {
    case S_IFBLK:
      printf("Block Device\n");
      break;
    case S_IFCHR:
      printf("Character device\n");
      break;
    case S_IFDIR:
      printf("Directory\n");
      break;
    case S_IFIFO:
      printf("FIFO / pipe\n");
      break;
    case S_IFLNK:
      printf("Symlink\n");
      break;
    case S_IFREG:
      printf("Regular File\n");
      break;
    case S_IFSOCK:
      printf("Socket\n");
      break;
    default:
      printf("Unknown\n");
      break;
  }
}

// output file info
void print_stats(const char *f_name) {
  int file_size;

  printf("[%s]\n", f_name);
  // show file size with [bytes]
  printf("File Size:    %lldbytes\n", info.st_size);
  // print file type
  print_file_type();
  // show last update time
  printf("Last Updated: %s\n", ctime(&info.st_mtime));
}

int main(int argc, char const *argv[]) {
  int i, fd;

  // if there is no params, show usage
  if (argc < 2)
    printf("usage: ./fview hoge.txt fuga ...\n");

  // get info and print info for each files got by params
  for (i = 1; i < argc; ++i){
    fd = open(argv[i], O_RDONLY);

    if (fd >= 0) {
      fstat(fd, &info);
      print_stats(argv[i]);
    } else {
      printf("Can't open. check: %s\n\n", argv[i]);
    }

    close(fd);
  }

  return 0;
}
