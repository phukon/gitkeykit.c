#include "../gitkeykit.h"

int check_secret_keys(void) {
  char command[256];
  FILE *fp;


  strncpy(command, "gpg --list-secret-keys", sizeof(command) - 1);
  fp = _popen(command, "r");
  if (fp == NULL) {
    return ERR_NO_SECRET_KEYS;
  }


  char line[1024];
  int found_secret_key = 0;

  // fgets() returns NULL when it reaches end of file or encounters an error
  // If successful, it returns the pointer to line
  // So the loop continues as long as there's more to read
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (strstr(line, "sec") != NULL) {
      found_secret_key = 1;
      break;
    }
  }

  if (!found_secret_key) {
    return ERR_NO_SECRET_KEYS;
  }

  _pclose(fp);
  return SUCCESS;
}
