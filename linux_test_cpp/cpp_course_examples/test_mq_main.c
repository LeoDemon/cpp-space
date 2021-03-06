#include </home/leodemon/leo/zeromq-4.0.3/include/zmq.h>
#include <string.h> 
#include <stdio.h> 
#include <unistd.h>  
#include <assert.h>

int main()
{
	// Socket to talk to clients
	void *context = zmq_ctx_new ();
	void *responder = zmq_socket (context, ZMQ_REP);
	int rc = zmq_bind (responder, "tcp://127.0.0.1:5555");
	printf ("rc==%d\n", rc);
	assert (rc == 0);

	while (1) {
		char buffer [10];
		zmq_recv (responder, buffer, 10, 0);
		printf ("Received Hello\n");
		sleep (1); // Do some 'work'
		zmq_send (responder, "World", 5, 0);
	}
	return 0;
}

