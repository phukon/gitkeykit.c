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
  // Check for GPG installation first
  char gpg_path[128];

  if (check_gpg_installation(gpg_path, sizeof(gpg_path)) != SUCCESS) {
    fprintf(stderr, "Error: GPG is not installed or not found in PATH\n");
    fprintf(stderr, "Please install GPG before using this tool\n");
    return ERR_GPG_NOT_FOUND;
  }

  printf("GPG program found at %s\n", gpg_path);

  if (check_git_installation() != SUCCESS) {
    fprintf(stderr, "Error: Git is not installed or not found in PATH\n");
    return ERR_GIT_NOT_FOUND;
  }

  printf("Git is installed.\n");

  if (argc < 2) {
    print_usage();
    return ERR_INVALID_ARGS;
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
