#include "../gitkeykit.h"

int create_pgp_key(void) {
  char response[10];
  int result;

  // result = system("gpg --version > /dev/null 2>&1");
  // if (result != 0) {
  //   printf("Error: GPG is not installed on your system.\n");
  //   return ERR_GPG_NOT_FOUND;
  // }

  printf("Do you want to create a new PGP key? (y/n): ");
  if (fgets(response, sizeof(response), stdin) == NULL) {
    return ERR_INVALID_INPUT;
  }

  if (response[0] == 'n' || response[0] == 'N') {
    printf("Aborting key creation.\n");
    return SUCCESS;
  }

  printf("Creating new PGP key...\n");
  
  // Execute GPG key generation with inherited stdio
  result = system("gpg --full-generate-key");
  if (result != 0) {
    printf("Error: Failed to generate GPG key.\n");
    return ERR_KEY_GENERATION;
  }

  printf("GPG key has been generated successfully.\n");
  return SUCCESS;
}