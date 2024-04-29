// This is header file for user related functionlity like registration, login etc.
#ifndef USER_H
#define USER_H
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 64
#define SALT_LEN 16

struct User {
    char username[MAX_USERNAME_LEN];
    char password[60]; // Length to accommodate bcrypt hash
    char salt[SALT_LEN];
};

int registerUser(const char *username, const char *password);
int loginUser(const char *username, const char *password);

#endif
