#include "Client.h"
#include "Server.h"
#include "PublicDef.h"
#include <pthread.h>

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Node/Tracker.h"
#include "Node/Node.h"
#include "Node/Routing.h"



// Globals...
///////////////////////////////////////////////NODE GLOBAL var
Node N1;
node * list ;
node * curr;
edge ** e_arr;
edge * e_head;


typedef struct argy {
    int portptr;
    dataset * data_file;
    node * node_list;
    edge ** edge_list;
} argy;



// void process_buffer(char *buffer, int max_len)
// {//ADDS NULL TO END OF STRING 
//     for (int i = 0; i < max_len; i++)
//     {
//         if ((buffer[i] == '\n') || (buffer[i] == '\r'))
//         {
//             buffer[i] = '\0';
//             break;
//         }
//     }
// }
pthread_mutex_t mutex;
int err=0;
void *ServerT( void* A){
    printf("IN server\n");
    argy *B = (argy *)A;
    int addr= B->portptr;
     node * node_list = B->node_list;
    edge ** edge_list = B->edge_list; 
    dataset* data_file = B->data_file;
    if(listen(sockfd,BACKLOG)<0)//-1 = errno
    {
        printf("INIT_Server socket Listening failed...\n");
        return 0;
    }
    printf("Listening...\n");
    //accept time how it works is somewhere will try to call coonect()
    //to the port im listening on..
    // Their connection will be queued waiting to be accepted()
    // you call accept tell it to get the pending connection
    // IT WILL RETURN A NEW SOCKFD FOR THIS CONNECTIONTHE FIRST SOCKFD IS STILL LISTENING FOR NEWCOMERS
    // BUT THE NEW ONE HANDLES SOLELY THE BACK AND FORTH WITH THIS CONN
    
while(1){
    sleep(3);//Sleep for a bit to allow the client to do stuff..a
    Recieve(addr, data_file, node_list, edge_list);//ATM NO NEED TO CALL ANYTHING BECAUSE WE USE GLOBAL VAR RN
// Command exits as connection is finished..
    //TODO simple messaging for DEV Please remove afterusage....
    }
    printf("all is well! :))\n");
    free(B);
    return 0;
}


int main(int argc, char *argv[]){
//////////////////////////////////////////////////////////////////
//Node Initialisation: place where node PORT is generated and its adress book...
/////////////////////////////////////////////////////////////////
    Node N1;
	if(!N1.init_node(argv)){
		printf("Err in init node (port id: %i)\n", atoi(argv[1]));
	}
    printf("file id: %i\n", N1.get_file()->id);
    int file = N1.get_file()->id;
    node * list = N1.get_node_list();
    node * curr = list;
    edge ** e_arr = (N1.get_edge_list());
    edge * e_head;
    PORT = N1.get_address();//GLOBALLY SETS PORT NUMBER 
    printf("Server thread start\n");
///////////////////////////////////////////////////////////////// 
//Server Section:
//////////////////////////////////////////////////////////////////
pthread_mutex_init(&mutex,NULL);
 argy A ;    //= (argy*)malloc(sizeof(argy));
int my_port = N1.get_address();
(A.portptr) = my_port;
(A).data_file = N1.get_data_list();
A.node_list = N1.get_node_list();
A.edge_list = N1.get_edge_list();
static pthread_t Serv;
int fail;
long xy;
 err =Server();
    if(err != 0 ){
        printf("Error on INIT Server see errors:\n");
        return 0;
    } 

xy = pthread_create(&Serv,NULL, ServerT ,&A);

if(xy){
    printf("@Thread ERROR\n");
    exit(-1);
}
int ch; 
printf("file id: %i\n", N1.get_file()->id);
printf("\nPlease Select the following options: >>>\n1.Publish File\n0.Quit\n Or ..Wait\n");
    printf("\nEnter choice:");

    do
    {
        scanf("%d", &ch);
        printf("file id: %i\n", N1.get_file()->id);
        switch (ch)
        {
        case 1:
            FileDistro(N1.get_file(),N1.get_address(), 
                    N1.get_node_list(), N1.get_map(), N1.get_edge_list());
            break;
            
        case 2:
            printf("Requesting FILE NOT YET ADDED\n Please try again.");
            break;
        case 0:
            printf("\nLeaving\n");
            break;
        default:
            printf("\nWrong choice\n");
        }
    } while (ch);
pthread_join(Serv,NULL);
// free(A);
pthread_mutex_destroy(&mutex);
    return 0;

}

int Server()
{
    // int sockfd , talkfd ;//SOCKET FILE DESCRIPTOR returns -1 on errno
    // struct sockaddr_in hints;
    // struct sockaddr_storage their_addr;
    // socklen_t addr_size;

    int force =1;
//     char *usrname =get_name    
//    printf("Username = %s",usrname);
    printf("Host Port number: %d",PORT);
    // struct sigaction sa;
    // int yes=1;
    // int rv1;
 if( (sockfd = socket(AF_INET, SOCK_STREAM ,0))==-1){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"INIT_Server getting socket: %s\n",gai_strerror(sockfd));
        return 1;//returning one as error check in main..
   }
   //Since we will be listening down the line we must bind the socket and the address...
  if (setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FD TO THE PORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    memset(&hints, 0, sizeof hints);//resets the struct so its not holding any memory.. 
    hints.sin_family = AF_INET;//Sets this to IPV4
    // = SOCK_STREAM;//TCP
    hints.sin_port = htons(PORT);//COnverts to big endian format.. Good practice
    hints.sin_addr.s_addr = INADDR_ANY;
   

//SIMPLE VERSION WILL NEED TO BE CHANGED DOWN THE LINE..
  
   if( bind(sockfd, (struct sockaddr *)&hints,sizeof(hints))<0   )//binds to the port we gave it to at the start.
    {
        printf("INIT_Server socket bind failed...\n");
        return 1;
    }
 

return 0;
}




void Recieve(unsigned address, dataset * data_file, node * node_list, edge ** edge_list)// delete after usage..
{
    
    fd_set active, read;
    addr_size=sizeof(their_addr);
    // Initialize my current set
    FD_ZERO(&active);
    FD_SET(sockfd, &active);
    int k=0;
    int n;
    char buff[MX_STR_LEN]={0};
        PORT = address;//GLOBALLY SETS PORT NUMBER 


        // TODO FIX THIS THINGY
      while (1)
    {
     
        read = active;

        if (select(FD_SETSIZE, &read, NULL, NULL, NULL) < 0)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
//service all the sockets with inputs pending//
        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &read))
            {
                        //connection request on orginal socket
                if (i == sockfd)
                {
                    int client_socket;
                    
                    if ((client_socket = accept(sockfd, (struct sockaddr *)&their_addr,
                                                (socklen_t *)&addr_size)) < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    printf("accepting message\n");
                    FD_SET(client_socket, &active);
                }
                else
                {
                    int REC_PORT = 0;
                    //data is arriving on an already connected socket
                    n = recv(i, buff, sizeof(buff), 0);
                    //Take
                    //Recieved buffer and parse first part;
                    //ADD ERROR COND FOR N
                    printf("my_port: %i\n", PORT);
                    printf("%s  = buff\n",buff);
                    REC_PORT = PortParser(buff);


                    if(REC_PORT == PORT)//Meant to be here 
                    {
                        int l = 0;
                        printf("Recieved Package!\n");
                        if(l = N1.add_file(buff, data_file)!=1)printf("Error on adding file to NODE Struct\n");//THis adds the file to a piece of memory like a pointer (NODES.CPP)
                    }
                    else
                    {//CONOR HELP WITH DEFS PLEASE HERE :)
                    //#FIXME: 
                        int NEXT_PORT = 0;
                        // edge ** e_list = X.get_edge_list;
                        // node * n_list = X.get_node_list;
                        printf("INT CHECK == %d\n",NEXT_PORT);
                        NEXT_PORT = shortest_path(PORT,REC_PORT,edge_list,node_list); //FIND NEXT BEST PLACE TO MOVE ON
                        printf("INT CHECK == %d\n",NEXT_PORT);
                        ClientCreate(NEXT_PORT,buff);//send it to this address and next port.
                    }//
                    close(i);
                    FD_CLR(i, &active);
                }
            }
        }

        if (k == (FD_SETSIZE * 2))
            break;
    }
    return;
}

////////////Client Functions://///////////////////////////////////////////////////////////////

int ClientCreate(int PORT_server,char *buffer)
{
    printf("In CLIENT\n");

int Csockfd =99;//SOCKET FILE DESCRIPTOR returns -1 on errno
    struct sockaddr_in Chints;// was using the addrinfo but doesnt work for single networking..
    char s[INET6_ADDRSTRLEN];//have it as length ipv6 incase good practise
    int yes =99;//DEFINING RANDOM NUMBERS
	int rv = 99,rz =99;

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024] = {0};
//  memset(&Chints, 0, sizeof Chints);//resets the struct so its not holding any memory.. 
    Chints.sin_family = AF_INET;//Sets this to IPV4
    // = SOCK_STREAM;//TCP
    Chints.sin_port = htons(PORT_server);//COnverts to big endian format.. Good practice
    Chints.sin_addr.s_addr = INADDR_ANY;

 

//create a socket from the info found 
if( (Csockfd = socket(AF_INET,SOCK_STREAM,0))<0){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"ERROR Client getting socket: %s\n",gai_strerror(Csockfd));
        return 1;//returning one as error check in main..
   }
int force =1;
 if (setsockopt(Csockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FileDESC TO THE PORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

if (connect(Csockfd, (struct sockaddr *)&Chints,sizeof Chints) == -1) {//connecting
            close(Csockfd);
            perror("ERROR client: connect");
			return 1;
}
printf("cLIENT FINE\n");
//TODO: Remove this later just for DEBUGging
// inet_ntop(Cres->ai_family, get_in_addr((struct sockaddr *)Cres->ai_addr),
//             s, sizeof s);
    printf("client: connecting to %s\n", s);

unsigned long ha =(MAX);

    	int n;
        char msg[2000] = {0};
        char X[1024] = {0};

	
    printf("Sending message:%s\n",buffer);
   
    //process_buffer(buffer, MAX);//adds the \0 instaed of \n 
    sprintf(msg, "%s",buffer); // format of data not entirely nesicary if we have enough spac in first array
    //Basically puts the string csv into this message and adds a \0 to make sure it sends correct.
    // this gets sent to the buffer

    send(Csockfd, msg, sizeof(msg), 0); // send to the created socket
    printf("\nMessage sent\n\n\n");
	

	// close the socket
	close(Csockfd);
 return 0;   
	
}
//NOTE SHOULD PASS IN NODE ADDRESSLIST
void FileDistro(dataset * file, int address, node * node_list,
                int * map, edge ** edge_list){//Generates the list of files and sends them
    int i = 0;
    //#FIXME:   
    //STEP 1 SPLITTING SEGMENT
    // STEP 2 IS ROUTING THE SEGMENT FINDING WHERE TO SEND IT FIRST
    //STEP 3 SEND THE PACKETS TO WHATEVER ROUTE FOUND BEST.        
    int seg = 100;
    int num_of_segs = 10;
    int seg_size = (file->char_count)/num_of_segs;
    int index = 0;
    
    printf("Finish init FileDistro\n");
    
    for(int i=0; i<num_of_segs; i++){
        char * message = (char*)malloc(MX_STR_LEN * sizeof(char));
        if(message==NULL){
            printf("Malloc Failed\n");
        }

        message = N1.share_file(file, seg, seg_size, index,
                                node_list, address);
         //that makes string into segments and assigns the segments to portn numbers in the form "111.5345."ARG""
        
        printf("Finished assembling segment %i.\n", seg);
        printf("%s\n\n", message);
        int DEST_PORT = PortParser(message); 
        int NEXT = shortest_path(address,DEST_PORT,edge_list,node_list);
        printf("Send seg %i to port %i\n\n", seg, NEXT);
        ClientCreate(NEXT,message);
        index = index + seg_size;
        seg++;
    }
  
    return;
}


int PortParser(char* buff){
    char * copy = (char*)malloc(MX_STR_LEN * sizeof(char));
    strcpy(copy, buff);
    char * parse = (char*)malloc(MX_STR_LEN * sizeof(char));
    parse = strtok(copy, ".");
    //printf("PASER SAYS %s.\n", parse);
    return atoi(parse);
}