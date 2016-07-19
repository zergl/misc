
#include "net_handler.h"

int main(int argc, char **argv)
{
	//NetHandler::instance()->Serve("127.0.0.1", 9090);
	NetHandler::instance()->Serve();
	return 0;
}

