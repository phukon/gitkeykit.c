#ifndef GITKEYKIT_H
#define GITKEYKIT_H

// Standard C Library headers
#include <stdio.h>      // Standard I/O operations
#include <stdlib.h>     // Standard library functions
#include <string.h>     // String manipulation functions
#include <errno.h>      // Error number definitions
#include <sys/stat.h>   // File status and information
#include <sys/types.h>  // Basic derived types
#include <fcntl.h>      // File control options
#include <ctype.h>      // Character type functions
#include <time.h>       // Time/date utilities

// ++++ ++++ ++++ ++++ ++++ ++++ ++++
#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #include <io.h> // for _access()
    #define PATH_SEPARATOR "\\"
    #define GPG_CHECK_CMD "where gpg"
    #define GIT_CHECK_CMD "where git"
    #define _popen _popen
    #define _pclose _pclose
#else
    #include <unistd.h>
    #include <sys/wait.h>
    #include <dirent.h>
    #define PATH_SEPARATOR "/"
    #define GPG_CHECK_CMD "which gpg"
    #define GIT_CHECK_CMD "which git"
    #define _popen popen
    #define _pclose pclose
#endif

// ++++ ++++ ++++ ++++ ++++ ++++ ++++
#define SUCCESS 0
#define ERR_GPG_NOT_FOUND 1
#define ERR_GIT_NOT_FOUND 2
#define ERR_INVALID_ARGS 3
#define ERR_NO_SECRET_KEYS 4
#define ERR_INVALID_INPUT 5
#define ERR_GIT_CONFIG 6
#define ERR_KEY_GENERATION 7
#define ERR_KEY_IMPORT 8
#define ERR_GIT_CONFIG_RESET 9
#define ERR_GPG_CONFIG_RESET 10
#define ERR_HOME_DIRECTORY_NOT_FOUND 11

// ++++ ++++ ++++ ++++ ++++ ++++ ++++
int check_gpg_installation(char *gpg_path, size_t path_size);
int check_git_installation(void);
int create_pgp_key(void);
int import_key(char * key_path);
// int import_pgp_key(const char *key_path);
int configure_git_gpg(const char *key_id);
int reset_configuration(void);
int check_required_dependencies(char *gpg_path, size_t path_size);
int check_secret_keys(char *gpg_path);
int set_git_config(char *gpg_path);
int add_extra_config(void);

#endif