#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

int main (int argc, char **argv) 
{
   redisReply *reply;
   redisContext *c;

   char user[20]="kesava";

   c = redisConnect("127.0.0.1", 6379);
   if (c->err) {
       printf("error: %s\n", c->errstr);
       return 1;
   }

   /* PINGs */
   reply = redisCommand(c,"get %s", user);
   printf("RESPONSE: %s\n", reply->str);
   freeReplyObject(reply);

   redisFree(c);
 
 }
