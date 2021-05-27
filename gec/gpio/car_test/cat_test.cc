#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define CAR_MAGIC 'h'
#define CAR_GO _IO(CAR_MAGIC, 1)
#define CAR_BACK _IO(CAR_MAGIC, 2)
#define CAR_STOP _IO(CAR_MAGIC, 3)
#define CAR_LEFT _IO(CAR_MAGIC, 4)
#define CAR_RIGHT _IO(CAR_MAGIC, 5)

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("./a.out <go | back | stop | left | right>\n");
    return 1;
  }
  int fd = 0;
  fd = open("/dev/Car", O_RDWR);
  if (fd < 0) {
    perror("open /dev/Car error");
    return 1;
  }
  if (!strcmp(argv[1], "go")) {
    ioctl(fd, CAR_GO, 0);
    printf("go\n");
  } else if (!strcmp(argv[1], "back")) {
    ioctl(fd, CAR_BACK, 0);
    printf("back\n");
  } else if (!strcmp(argv[1], "stop")) {
    ioctl(fd, CAR_STOP, 0);
    printf("stop\n");
  } else if (!strcmp(argv[1], "left")) {
    ioctl(fd, CAR_LEFT, 0);
    printf("left\n");
  } else if (!strcmp(argv[1], "right")) {
    ioctl(fd, CAR_RIGHT, 0);
    printf("right\n");
  } else {
    printf("your choose wrong!\n");
    printf("./a.out <go | back | stop | left | right>\n");
  }
  close(fd);
  return 0;
}
