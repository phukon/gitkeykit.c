#include "../gitkeykit.h"

int start(void) {
  char gpg_path[128];
  check_required_dependencies(gpg_path, sizeof(gpg_path));
  check_secret_keys(gpg_path);

}