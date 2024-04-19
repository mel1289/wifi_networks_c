#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char cmd[] = "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -s | grep ' SSID'";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("failed to run command");
        exit(1);
    }

    printf("NETWORKS:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *pos;
        if ((pos = strstr(buffer, " SSID: ")) != NULL) {
            pos += 7;
            char *end = strchr(pos, '\n');
            if (end) *end = '\0';
            printf("%s\n", pos);
        }
    }

    return 0;
}
