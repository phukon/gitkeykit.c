#include "../gitkeykit.h"

int set_git_config(char *gpg_path) {
  char username[128];
  char email[128];


  printf("Enter your name: ");
  if (fgets(username, sizeof(username), stdin) == NULL) {
    fprintf(stderr, "Error reading username\n");
    return ERR_INVALID_INPUT;
  }
  // removing the newline character
  username[strcspn(username, "\n")] = 0;

  printf("Enter your email: ");
  if (fgets(email, sizeof(email), stdin) == NULL) {
    fprintf(stderr, "Error reading email\n");
    return ERR_INVALID_INPUT;
  }
  email[strcspn(email, "\n")] = 0;


}
