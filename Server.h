#ifndef Server_h
#define Server_h

#include "Node/Tracker.h"

//SFUNCTIONS
int Server();
int ListenA();


//TODO REMOVE || MODIFY HEAVILY
// void *get_in_addr(struct sockaddr *sa); Defined in Client already
void Recieve(unsigned address, dataset * data_file, node * node_list, edge ** edge_list);  // Simple chat program which generates a string and sends it.


#endif  