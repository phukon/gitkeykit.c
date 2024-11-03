#include "gitkeykit.h"

int configure_git_gpg(const char* key_id) {
    char command[512];

    // Configure Git to use GPG signing
    system("git config --global commit.gpgsign true");
    
    // Set the signing key
    snprintf(command, sizeof(command), "git config --global user.signingkey %s", key_id);
    system(command);

    // Configure GPG program path
    #ifdef _WIN32
        system("git config --global gpg.program \"C:/Program Files (x86)/GnuPG/bin/gpg.exe\"");
    #else
        system("git config --global gpg.program gpg");
    #endif

    return SUCCESS;
}

int reset_configuration(void) {
    system("git config --global --unset commit.gpgsign");
    system("git config --global --unset user.signingkey");
    system("git config --global --unset gpg.program");
    return SUCCESS;
}