#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gpg_handler.h"
#include "logger.h"

#ifdef _WIN32
    #define GPG_DEFAULT_PATH "C:\\Program Files (x86)\\GnuPG\\bin\\gpg.exe"
#else
    #define GPG_DEFAULT_PATH "/usr/bin/gpg"
#endif

bool check_gpg_installation(void) {
    #ifdef _WIN32
        return (system("where gpg > nul 2>&1") == 0);
    #else
        return (system("which gpg > /dev/null 2>&1") == 0);
    #endif
}

bool import_gpg_key(const char *key_path) {
    if (key_path == NULL) {
        log_error("Invalid key path");
        return false;
    }

    // Check if file exists
    FILE *file = fopen(key_path, "r");
    if (file == NULL) {
        log_error("Could not open key file");
        return false;
    }
    fclose(file);

    // Build the import command
    char command[MAX_PATH_LENGTH * 2];
    #ifdef _WIN32
        snprintf(command, sizeof(command), "gpg --import \"%s\"", key_path);
    #else
        snprintf(command, sizeof(command), "gpg --import '%s'", key_path);
    #endif

    // Execute the import command
    int result = system(command);
    if (result != 0) {
        log_error("Failed to import GPG key");
        return false;
    }

    log_success("GPG key imported successfully");
    return true;
}

bool create_gpg_key(GPGKeyInfo *key_info) {
    // Create a temporary batch file for key generation
    FILE *batch_file = fopen("key_gen.batch", "w");
    if (!batch_file) {
        log_error("Failed to create batch file");
        return false;
    }

    fprintf(batch_file, 
        "Key-Type: RSA\n"
        "Key-Length: 4096\n"
        "Name-Real: %s\n"
        "Name-Email: %s\n"
        "Expire-Date: 0\n"
        "%s\n"
        "%%commit\n",
        key_info->name,
        key_info->email,
        "%%no-protection");

    fclose(batch_file);

    // Execute GPG key generation
    int result = system("gpg --batch --generate-key key_gen.batch");
    remove("key_gen.batch");

    if (result != 0) {
        log_error("Failed to generate GPG key");
        return false;
    }

    // Get the generated key ID
    FILE *fp = popen("gpg --list-secret-keys --with-colons | grep sec | cut -d: -f5", "r");
    if (fp == NULL) {
        log_error("Failed to get key ID");
        return false;
    }

    fgets(key_info->key_id, MAX_KEY_ID_LENGTH, fp);
    pclose(fp);

    return true;
}