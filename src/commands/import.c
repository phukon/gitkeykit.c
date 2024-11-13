#include "../gitkeykit.h"

int import_key(char * key_path) {
  if (!key_path) {
    return ERR_KEY_IMPORT;
  }

  // Check if file exists and is readable
  #ifdef _WIN32
    if (_access(key_path, 4) != 0) {  // 4 is for read permission
      return ERR_KEY_IMPORT;
    }
  #else
    if (access(key_path, R_OK) != 0) {
      return ERR_KEY_IMPORT;
    }
  #endif

  int result;

  // allocating memory for the command string
  // length of "gpg --import " + key_path + null terminator
  size_t cmd_len = strlen("gpg --import ") + strlen(key_path) + 1;
  char *command = malloc(cmd_len);

  if (!command) {
    return ERR_KEY_IMPORT;
  }

  // building the command string safely
  if (snprintf(command, cmd_len, "gpg --import %s", key_path) < 0) {
    free(command);
    return ERR_KEY_IMPORT;
  }

  result = system(command);
  free(command);

  #ifdef _WIN32
    if (result == -1) {
      return ERR_KEY_IMPORT;
    }
  #else
    if (result == -1 || WEXITSTATUS(result) != 0) {
      return ERR_KEY_IMPORT;
    }
  #endif

  return SUCCESS;
}