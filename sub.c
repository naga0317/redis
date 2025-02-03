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

    redisReply *reply = redisCommand(c, "SUBSCRIBE mychannel");
    freeReplyObject(reply);

    while (1) {
        redisReply *msg;
        if (redisGetReply(c, (void**)&msg) == REDIS_OK) {
            if (msg->type == REDIS_REPLY_ARRAY && msg->elements == 3) {
                printf("Received message: %s\n", msg->element[2]->str);
            }
            freeReplyObject(msg);
        }
    }

    redisFree(c);
    return 0;
}
