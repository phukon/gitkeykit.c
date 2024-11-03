#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "git_config.h"
#include "logger.h"

bool configure_git(const GPGKeyInfo *key_info) {
    char cmd[1024];
    
    // Configure git user name
    snprintf(cmd, sizeof(cmd), "git config --global user.name \"%s\"", key_info->name);
    if (system(cmd) != 0) {
        log_error("Failed to configure git user name");
        return false;
    }

    // Configure git email
    snprintf(cmd, sizeof(cmd), "git config --global user.email \"%s\"", key_info->email);
    if (system(cmd) != 0) {
        log_error("Failed to configure git email");
        return false;
    }

    // Configure signing key
    snprintf(cmd, sizeof(cmd), "git config --global user.signingkey %s", key_info->key_id);
    if (system(cmd) != 0) {
        log_error("Failed to configure signing key");
        return false;
    }

    // Enable commit signing
    if (system("git config --global commit.gpgsign true") != 0) {
        log_error("Failed to enable commit signing");
        return false;
    }

    return true;
}