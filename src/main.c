#include "gitkeykit.h"

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
    return start();
  }

  if (strcmp(argv[1], "--reset") == 0) {
    return reset();
  } else if (strcmp(argv[1], "--help") == 0) {
    print_usage();
    return 0;
  } else if (strcmp(argv[1], "import") == 0) {
    if (argc != 3) {
      fprintf(stderr, "Error: Import command requires a key path\n");
      return ERR_INVALID_ARGS;
    }
    return import_key(argv[2]);
  }

  print_usage();
  return ERR_INVALID_ARGS;
}
