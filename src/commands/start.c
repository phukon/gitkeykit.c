#include "../gitkeykit.h"


int start(void) {
  char gpg_path[128];
  check_required_dependencies(gpg_path, sizeof(gpg_path));
  if (check_secret_keys() != SUCCESS) {
    create_pgp_key();
  }

  set_git_config(gpg_path);
  
  #ifndef _WIN32
  add_extra_config();
  #endif

  printf("Setup complete. Happy coding!\n");
  return SUCCESS;
}