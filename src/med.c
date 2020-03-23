#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios originTermios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &originTermios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &originTermios);
  atexit(disableRawMode);

  struct termios raw = originTermios;
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
  enableRawMode();

  char c = 0;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'); 
  return 0;
}
