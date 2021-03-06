#include </home/leodemon/leo/zeromq-4.0.3/include/zmq.h>
#include <string.h> 
#include <stdio.h> 
#include <unistd.h>  

int main () 

{     

	void *context = zmq_init (1); //  Socket to talk to server     

	printf ("Connecting to hello world server...\n");     

	void *requester = zmq_socket (context, ZMQ_REQ);     

	zmq_connect(requester, "tcp://127.0.0.1:5555");       

	int request_nbr;     

	for (request_nbr = 0; request_nbr != 10; request_nbr++) 

	{         

		//zmq_msg_t request;         

		//zmq_msg_init_data (&request, "Hello", 6, NULL, NULL);         

		printf ("Sending request %d...\n", request_nbr);         

		//zmq_send(requester, &request, 6, 0); 
		int rc = zmq_send(requester, "china", 5, 0); 

		printf("send over---rc==%d\n", rc); 

		//zmq_msg_close (&request);           

		zmq_msg_t reply;         

		zmq_msg_init (&reply);         

		zmq_recv (requester, &reply, 0,0);         

		printf ("Received reply %d: [%s]\n", request_nbr, (char *) zmq_msg_data (&reply));         

		zmq_msg_close (&reply);     

	}     

	zmq_close (requester);     

	zmq_term (context);     

	return 0; 

}

