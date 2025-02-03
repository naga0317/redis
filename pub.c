#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

int main() {
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        printf("Error connecting to Redis\n");
        return 1;
    }

    char message[256];
    while (1) {
        printf("Enter message to publish (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);
        
        if (strncmp(message, "exit", 4) == 0) break;

        redisReply *reply = redisCommand(c, "PUBLISH mychannel %s", message);
        freeReplyObject(reply);
    }

    redisFree(c);
    return 0;
}
