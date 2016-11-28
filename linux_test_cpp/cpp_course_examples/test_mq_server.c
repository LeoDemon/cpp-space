#include </home/leodemon/leo/zeromq-4.0.3/include/zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (void)

{

	void *context = zmq_init (1);

	// Socket to talk to clients

	void *responder = zmq_socket (context, ZMQ_REP);

	zmq_bind (responder, "tcp://127.0.0.1:5555");

	printf("binding on port 5555.\nwaiting client send message...\n");

	while (1) {

		// Wait for next request from client

		zmq_msg_t request;

		zmq_msg_init (&request);

		char buf[32];

		zmq_recv(responder,buf, &request, 0);

		int size = zmq_msg_size (&request);

		char *string = malloc (size + 1);

		memset(string,0,size+1);

		memcpy (string, zmq_msg_data (&request), size);

		printf ("Received Hello string=[%s]\n",string);

		free(string);

		zmq_msg_close (&request);

		// Do some 'work'

		sleep (1);

		// Send reply back to client

		zmq_msg_t reply;

		char res[128]={0};

		snprintf(res,127,"reply:%d",random());

		zmq_msg_init_size (&reply, strlen(res));

		memcpy (zmq_msg_data (&reply), res, strlen(res));

		char buf2[32];

		zmq_send (responder, buf2, &reply, 0);

		zmq_msg_close (&reply);

	}

	// We never get here but if we did, this would be how we end

	zmq_close (responder);

	zmq_term (context);

	return 0;

}
