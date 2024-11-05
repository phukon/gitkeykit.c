#include "gitkeykit.h"

#ifdef _WIN32
#define GPG_CHECK_CMD "where gpg"
#define GIT_CHECK_CMD "where git"
#else
#define GPG_CHECK_CMD "which gpg"
#define GIT_CHECK_CMD "which git"
#endif

int check_gpg_installation(char *gpg_path, size_t path_size) {
  FILE *fp;
  char result[128];

  fp = _popen(GPG_CHECK_CMD, "r");
  if (fp == NULL) {
    return ERR_GPG_NOT_FOUND;
  }

  if (fgets(result, sizeof(result), fp) != NULL) {
    strncpy_s(gpg_path, path_size, result, _TRUNCATE);
    _pclose(fp);
    return SUCCESS;
  }

  _pclose(fp);
  return ERR_GPG_NOT_FOUND;
}

int check_git_installation(void) {
  return system(GIT_CHECK_CMD) == 0 ? SUCCESS : ERR_GIT_NOT_FOUND;
}
