#ifndef GPG_HANDLER_H
#define GPG_HANDLER_H

#include <stdbool.h>

#define MAX_KEY_ID_LENGTH 256
#define MAX_PATH_LENGTH 1024

typedef struct {
    char key_id[MAX_KEY_ID_LENGTH];
    char email[256];
    char name[256];
    char passphrase[256];
} GPGKeyInfo;

bool check_gpg_installation(void);
bool create_gpg_key(GPGKeyInfo *key_info);
bool import_gpg_key(const char *key_path);
bool configure_pinentry(void);
char* get_gpg_program_path(void);

#endif