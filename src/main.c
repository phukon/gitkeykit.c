#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpg_handler.h"
#include "git_config.h"
#include "logger.h"

void print_usage(void) {
    printf("Usage: pgp-git-helper [create|import] [options]\n");
    printf("Options:\n");
    printf("  create - Create new GPG key\n");
    printf("  import <key_path> - Import existing GPG key\n");
}

int main(int argc, char *argv[]) {
    if (!check_gpg_installation()) {
        log_error("GPG is not installed. Please install GPG first.");
        return 1;
    }

    if (argc < 2) {
        print_usage();
        return 1;
    }

    GPGKeyInfo key_info = {0};

    if (strcmp(argv[1], "create") == 0) {
        printf("Enter your name: ");
        fgets(key_info.name, sizeof(key_info.name), stdin);
        key_info.name[strcspn(key_info.name, "\n")] = 0;

        printf("Enter your email: ");
        fgets(key_info.email, sizeof(key_info.email), stdin);
        key_info.email[strcspn(key_info.email, "\n")] = 0;

        if (!create_gpg_key(&key_info)) {
            return 1;
        }
    } else if (strcmp(argv[1], "import") == 0) {
        if (argc < 3) {
            log_error("Please provide key path");
            return 1;
        }
        if (!import_gpg_key(argv[2])) {
            return 1;
        }
    } else {
        print_usage();
        return 1;
    }

    if (!configure_git(&key_info)) {
        return 1;
    }

    log_success("GPG key setup and Git configuration completed successfully!");
    return 0;
}