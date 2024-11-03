#include "gitkeykit.h"

int create_pgp_key(void) {
    // Set pinentry-mode to loopback for secure passphrase entry
    system("gpg --command-fd 0 --status-fd 1 --pinentry-mode loopback "
          "--quick-generate-key \"$(git config user.name) <$(git config user.email)>\" rsa4096");
    
    // Get the newly created key ID
    FILE *fp = popen("gpg --list-secret-keys --keyid-format LONG | grep sec | cut -d'/' -f2 | cut -d' ' -f1", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to get key ID\n");
        return 1;
    }

    char key_id[65];
    fgets(key_id, sizeof(key_id), fp);
    key_id[strcspn(key_id, "\n")] = 0;
    pclose(fp);

    return configure_git_gpg(key_id);
}

int import_pgp_key(const char* key_path) {
    char command[512];
    snprintf(command, sizeof(command), "gpg --import \"%s\"", key_path);
    
    if (system(command) != 0) {
        fprintf(stderr, "Failed to import key\n");
        return 1;
    }

    return SUCCESS;
}