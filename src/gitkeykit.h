#ifndef GITKEYKIT_H
#define GITKEYKIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

// Return codes
#define SUCCESS 0
#define ERR_GPG_NOT_FOUND 1
#define ERR_GIT_NOT_FOUND 2
#define ERR_INVALID_ARGS 3
#define ERR_NO_SECRET_KEYS 4
#define ERR_INVALID_INPUT 5
#define ERR_GIT_CONFIG 6

// Function declarations
int check_gpg_installation(char *gpg_path, size_t path_size);
int check_git_installation(void);
int create_pgp_key(void);
int import_pgp_key(const char *key_path);
int configure_git_gpg(const char *key_id);
int reset_configuration(void);
int check_required_dependencies(char *gpg_path, size_t path_size);
int check_secret_keys(char *gpg_path);

#endif
