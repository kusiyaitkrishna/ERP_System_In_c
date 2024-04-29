#include "user.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void generateRandomSalt(char *salt) {
    // Generate a random salt using a simple algorithm
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int salt_len = SALT_LEN - 1;
    for (int i = 0; i < salt_len; i++) {
        int index = rand() % (sizeof(charset) - 1);
        salt[i] = charset[index];
    }
    salt[salt_len] = '\0';
}

int saveUserToFile(const char *username, const char *password, const char *salt) {
    FILE *fp = fopen("users.txt", "a"); // Open in append mode
    if (fp == NULL) {
        fprintf(stderr, "Error opening user database.\n");
        return 0;
    }
    fprintf(fp, "%s|%s|%s\n", username, password, salt);
    fclose(fp);
    return 1;
}

struct User loadUserFromFile(const char *username) {
    struct User user;
    user.username[0] = '\0'; // Initialize as empty

    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        return user;
    }

    char line[128];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token = strtok(line, "|");
        if (strcmp(token, username) == 0) {
            strcpy(user.username, token);
            strcpy(user.password, strtok(NULL, "|"));
            strcpy(user.salt, strtok(NULL, "|"));
            break;
        }
    }
    fclose(fp);
    return user;
}

int registerUser(const char *username, const char *password) {
    if (strlen(username) >= MAX_USERNAME_LEN || strlen(password) >= MAX_PASSWORD_LEN) {
        fprintf(stderr, "Username or password too long.\n");
        return 0;
    }

    char salt[SALT_LEN];
    generateRandomSalt(salt);

    return saveUserToFile(username, password, salt);
}

int loginUser(const char *username, const char *password) {
    struct User user = loadUserFromFile(username);
    if (user.username[0] == '\0') {
        return 0;
    }

    return strcmp(password, user.password) == 0;
}