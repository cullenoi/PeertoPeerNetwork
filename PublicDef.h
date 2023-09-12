#ifndef PublicDef_h
#define PublicDef_h
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h> // bzero()
#include <netinet/in.h>
#include <unistd.h> // read(), write(), close()
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/select.h>

#include "Node/Node.h"
#include "Node/Tracker.h"

 int sockfd , talkfd ;//SOCKET FILE DESCRIPTOR returns -1 on errno
 struct sockaddr_in hints;
 struct sockaddr_in their_addr;
 socklen_t addr_size;


#define _SS_PAD1SIZE 3000
#define BACKLOG 10   // how many pending connections queue will hold
#define MAX 100
#define SA struct sockaddr
/////////server side//

/// @brief CLIENT SIDE///// These could be made simply as called in function noneeed fr global
int PORT;
void FileDistro(dataset * file, int address, node * node_list,
                int * map, edge ** edge_list);

int PortParser(char *buff);



#endif 