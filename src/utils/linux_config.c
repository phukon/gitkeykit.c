#include "../gitkeykit.h"

static int create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        return mkdir(path, 0700);
    }
    return 0;
}

static int append_to_file(const char *filepath, const char *content) {
    FILE *file = fopen(filepath, "a");
    if (!file) {
        return -1;
    }
    fprintf(file, "%s\n", content);
    fclose(file);
    return 0;
}

int add_extra_config(void) {
    char gpg_conf_path[512];
    char gnupg_dir[512];
    char *home_dir;

    home_dir = getenv("HOME");
    if (!home_dir) {
        fprintf(stderr, "Error: Could not get home directory\n");
        return ERR_INVALID_INPUT;
    }

    snprintf(gnupg_dir, sizeof(gnupg_dir), "%s/.gnupg", home_dir);
    snprintf(gpg_conf_path, sizeof(gpg_conf_path), "%s/gpg.conf", gnupg_dir);

    if (create_directory(gnupg_dir) != 0) {
        fprintf(stderr, "Error: Could not create .gnupg directory\n");
        return ERR_INVALID_INPUT;
    }

    // Clear or create gpg.conf
    FILE *file = fopen(gpg_conf_path, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open gpg.conf\n");
        return ERR_INVALID_INPUT;
    }
    fclose(file);

    if (append_to_file(gpg_conf_path, "use-agent") != 0 ||
        append_to_file(gpg_conf_path, "pinentry-mode loopback") != 0) {
        fprintf(stderr, "Error: Could not write to gpg.conf\n");
        return ERR_INVALID_INPUT;
    }

    // Kill gpg-agent
    if (system("gpgconf --kill gpg-agent") != 0) {
        fprintf(stderr, "Warning: Could not kill gpg-agent\n");
    } else {
        printf("gpg-agent killed.\n");
    }

    // Start gpg-agent
    if (system("gpg-agent --daemon") != 0) {
        fprintf(stderr, "Warning: Could not start gpg-agent\n");
    } else {
        printf("gpg-agent restarted.\n");
    }

    printf("\n╭─────────────────────────────────────────────╮\n");
    printf("│                                             │\n");
    printf("│  Changes written to GPG config.             │\n");
    printf("│  (~/.gnupg/gpg.conf)                       │\n");
    printf("│                                             │\n");
    printf("│  > use-agent                               │\n");
    printf("│  > pinentry-mode loopback                  │\n");
    printf("│                                             │\n");
    printf("╰─────────────────────────────────────────────╯\n");

    return SUCCESS;
}