#include "../gitkeykit.h"

int check_required_dependencies(char *gpg_path, size_t path_size) {
    // Check for GPG installation first
    if (check_gpg_installation(gpg_path, path_size) != SUCCESS) {
        fprintf(stderr, "Error: GPG is not installed or not found in PATH\n");
        fprintf(stderr, "Please install GPG before using this tool\n");
        return ERR_GPG_NOT_FOUND;
    }

    printf("GPG program found at %s\n", gpg_path);

    if (check_git_installation() != SUCCESS) {
        fprintf(stderr, "Error: Git is not installed or not found in PATH\n");
        return ERR_GIT_NOT_FOUND;
    }

    printf("Git is installed.\n");
    
  return SUCCESS;
}
