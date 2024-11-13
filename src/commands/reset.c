#include "../gitkeykit.h"


int clear_gpg_config(void) {
  char gnupg_dir[1024];
  char gpg_conf_path[1024];
  char *home_dir;
  struct stat st = {0};

  home_dir = getenv("HOME");
  if (!home_dir) {
    fprintf(stderr, "Error: Could not get the home directory\n");
    return ERR_HOME_DIRECTORY_NOT_FOUND;
  }

  if (snprintf(gnupg_dir, sizeof(gnupg_dir), "%s/.gnupg", home_dir) >= (int)sizeof(gnupg_dir)) {
    fprintf(stderr, "Error: gnupg_dir buffer overflow\n");
    return ERR_BUFFER_OVERFLOW;
  }

  if (stat(gnupg_dir, &st) == -1) {
    return SUCCESS; // No gnupg directory, so no config to clear
  }

  if (snprintf(gpg_conf_path, sizeof(gpg_conf_path), "%s/gpg.conf", gnupg_dir) >= (int)sizeof(gpg_conf_path)) {
    fprintf(stderr, "Error: gpg_conf_path buffer overflow\n");
    return ERR_BUFFER_OVERFLOW;
  }

  FILE *file = fopen(gpg_conf_path, "w");
  if (!file) {
    fprintf(stderr, "Error: Could not open gpg.conf for clearing\n");
    return ERR_GPG_CONFIG_RESET;
  }
  fclose(file);

  printf("GPG configuration cleared.\n");
  return SUCCESS;
}


int reset(void) {
  const char *cmd = 
      "git config --global --unset user.name &&"
      "git config --global --unset user.email &&"
      "git config --global --unset user.signingkey &&"
      "git config --global --unset commit.gpgsign &&"
      "git config --global --unset tag.gpgsign &&"
      "git config --global --unset gpg.program";

  int result = system(cmd);
  if(result != 0) {
    printf("Error: Failed to reset git configuration.\n");
    return ERR_GIT_CONFIG_RESET;
  }

  #ifndef _WIN32
    clear_gpg_config();
  #endif

  printf("Git configuration reset successfully.\n");
  return SUCCESS;
}