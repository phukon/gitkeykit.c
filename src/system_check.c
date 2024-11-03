#include "gitkeykit.h"

#ifdef _WIN32
    #define GPG_CHECK_CMD "where gpg.exe"
    #define GIT_CHECK_CMD "where git.exe"
#else
    #define GPG_CHECK_CMD "which gpg"
    #define GIT_CHECK_CMD "which git"
#endif

int check_gpg_installation(void) {
    return system(GPG_CHECK_CMD) == 0 ? SUCCESS : ERR_GPG_NOT_FOUND;
}

int check_git_installation(void) {
    return system(GIT_CHECK_CMD) == 0 ? SUCCESS : ERR_GIT_NOT_FOUND;
}