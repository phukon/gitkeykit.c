#include "../gitkeykit.h"

int set_git_config(char *gpg_path) {
  char username[128];
  char email[128];
  char command[128];
  char line[1024];
  FILE *fp;
  char key_fingerprint[128] = "";
  size_t max_length = 0;

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

  printf("Setting git config...\n");

  strncpy(command, "gpg --list-secret-keys", sizeof(command) - 1);
  fp = _popen(command, "r");
  if (fp == NULL) {
    return ERR_NO_SECRET_KEYS;
  }

  while(fgets(line, sizeof(line), fp) != NULL) {
    // Tokenize the line using strtok
    char *token = strtok(line, " \t\n");
    
    while (token != NULL) {
      size_t token_len = strlen(token);
      if (token_len > max_length) {
        strncpy(key_fingerprint, token, sizeof(key_fingerprint) - 1);
        key_fingerprint[sizeof(key_fingerprint) - 1] = '\0';
        max_length = token_len;
      }
      token = strtok(NULL, " \t\n");
    }
  }

  _pclose(fp);

  if (max_length == 0) {
    fprintf(stderr, "No GPG key found\n");
    return ERR_NO_SECRET_KEYS;
  }

  printf("Found GPG key: %s\n", key_fingerprint);

  // Setting git config
  char git_command[256];

  // Set user name
  snprintf(git_command, sizeof(git_command), "git config --global user.name \"%s\"", username);
  if (system(git_command) != 0) {
    fprintf(stderr, "Error setting git username\n");
    return ERR_GIT_CONFIG;
  }

  // Set user email
  snprintf(git_command, sizeof(git_command), "git config --global user.email \"%s\"", email);
  if (system(git_command) != 0) {
    fprintf(stderr, "Error setting git email\n");
    return ERR_GIT_CONFIG;
  }

  // Set signing key
  snprintf(git_command, sizeof(git_command), "git config --global user.signingkey %s", key_fingerprint);
  if (system(git_command) != 0) {
    fprintf(stderr, "Error setting signing key\n");
    return ERR_GIT_CONFIG;
  }

  // Enable commit signing
  if (system("git config --global commit.gpgsign true") != 0) {
    fprintf(stderr, "Error enabling commit signing\n");
    return ERR_GIT_CONFIG;
  }

  // Enable tag signing
  if (system("git config --global tag.gpgsign true") != 0) {
    fprintf(stderr, "Error enabling tag signing\n");
    return ERR_GIT_CONFIG;
  }

  // Set GPG program path
  snprintf(git_command, sizeof(git_command), "git config --global gpg.program \"%s\"", gpg_path);
  if (system(git_command) != 0) {
    fprintf(stderr, "Error setting GPG program path\n");
    return ERR_GIT_CONFIG;
  }

  printf("Git configurations applied successfully\n");
  return SUCCESS;
}
