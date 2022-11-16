#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX 10
  
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
    int count = 5;
  
    // ftok to generate unique key
    key = ftok("/tmp/naseeb.txt", 65);
    message.mesg_type = 1;
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    sprintf(message.mesg_text, "%s", "Aaseeb Panghal");
    
    for(;;)
    {
        // msgsnd to send message
        //msgsnd(msgid, &messageType, 0, 0);
        message.mesg_text[0]++;
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Data send is : %s \n", message.mesg_text);
        usleep(1000000);
    }
  
    // display the message
  
    return 0;
}
