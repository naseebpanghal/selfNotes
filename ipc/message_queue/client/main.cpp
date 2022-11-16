#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
  
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
static int messageType=0;
  
int main()
{
    key_t key;
    int msgid;
  
    int count = 0;
    // ftok to generate unique key
    key = ftok("/tmp/naseeb.txt", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    for(;;)
    {
        // msgrcv to receive message
        //msgrcv(msgid, &messageType, 0, 1, 0);
        msgrcv(msgid, &message, sizeof(message), 1, 0);

        // display the message
        printf("Data Received is : %s \n", message.mesg_text);
        usleep(1000000);
    }
  
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}
