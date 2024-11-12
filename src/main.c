/*
 * TODO:
 * [x] check gpg in system
 * [x] check git install
 * [] check for secret keys
 * [x] list secret keys
 * [] set gitconfig with the key
 *
 * [] generate keys if not present
 * [] set gitconfig with the key
 *
 * [] configure gpg if linux
 * [] add config to gpg config
 * [] write the pin entry thing
 * [] kill the gpg agent
 * [] start the gpg agent
 */

#include "gitkeykit.h"
#include <stdio.h>

void print_usage(void) {
  printf("Usage: gitkeykit [COMMAND] [OPTIONS]\n");
  printf("\nCommands:\n");
  printf("  create              Create a new PGP key\n");
  printf("  import <key_path>   Import PGP key from file\n");
  printf("  --reset            Reset Git and GPG configurations\n");
  printf("\nExample:\n");
  printf("  gitkeykit create\n");
  printf("  gitkeykit import key.txt\n");
}

int main(int argc, char *argv[]) {

  if (argc == 1) {
    // return check_required_dependencies();
  }

  if (strcmp(argv[1], "--reset") == 0) {
    return reset_configuration();
  } else if (strcmp(argv[1], "create") == 0) {
    return create_pgp_key();
  } else if (strcmp(argv[1], "import") == 0) {
    if (argc != 3) {
      fprintf(stderr, "Error: Import command requires a key path\n");
      return ERR_INVALID_ARGS;
    }
    return import_pgp_key(argv[2]);
  }

  print_usage();
  return ERR_INVALID_ARGS;

}
