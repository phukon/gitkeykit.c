#include "gitkeykit.h"

int check_gpg_installation(char *gpg_path, size_t path_size) {
  FILE *fp;
  char result[128];

  fp = _popen(GPG_CHECK_CMD, "r");
  if (fp == NULL) {
    return ERR_GPG_NOT_FOUND;
  }

  if (fgets(result, sizeof(result), fp) != NULL) {
    #ifdef _WIN32
      strncpy_s(gpg_path, path_size, result, _TRUNCATE);
    #else
      strncpy(gpg_path, result, path_size - 1);
      gpg_path[path_size - 1] = '\0';
    #endif
    _pclose(fp);
    return SUCCESS;
  }

  _pclose(fp);
  return ERR_GPG_NOT_FOUND;
}

int check_git_installation(void) {
  return system(GIT_CHECK_CMD) == 0 ? SUCCESS : ERR_GIT_NOT_FOUND;
}
