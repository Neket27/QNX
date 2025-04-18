#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h>
#include <ctype.h>

void removeConsonants(char *str) {
    int i, j = 0;
    char vowels[] = "aeiouAEIOU";
    int len = strlen(str);
    char result[512];

    for (i = 0; i < len; i++) {
        if (strchr(vowels, str[i]) || !isalpha(str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    strcpy(str, result);
}

int main(void){
    int rcvid;
    int child;
    char message[512];
    printf("Server start working\n");
    child = ChannelCreate(0);
    printf("Channel id %d \n", child);
    printf("Pid %d \n", getpid());

    while (1) {
        rcvid = MsgReceive(child, message, sizeof(message), NULL);
        printf("Receive message rcvid=%X \n", rcvid);
        printf("Request text: \"%s\".\n", message);
        removeConsonants(message);
        MsgReply(rcvid, EOK, message, sizeof(message));
        printf("Response text: \"%s\".\n", message);
    }
    return 0;
}
