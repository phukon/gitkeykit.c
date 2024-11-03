#ifndef GIT_CONFIG_H
#define GIT_CONFIG_H

#include "gpg_handler.h"

bool configure_git(const GPGKeyInfo *key_info);
bool check_git_installation(void);

#endif