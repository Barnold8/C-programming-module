/*
 *  NetworkServer.c
 *  ProgrammingPortfolio Skeleton
 *
 */

/* You will need to include these header files to be able to implement the TCP/IP functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <ctype.h> 
#include <string.h>

/* You will also need to add #include for your graph library header files */

#include "graph.h"
#include "dijkstra.h"
#include "linked_list.h"

#define kBufSize 12
/* Defining server macros (state macros) */
#define TAKING_INPUT 0
#define CLOSING_CONNECTION 1

/* Defining server macros (state macros) */

#define SERVER_ADDR 1818
#define DATA_BUFFER 130

void ReadLineFromNetwork(int fd, char *buf, int size)
{
	char l[kBufSize+1];
	ssize_t n;
	int cline = 0;
	char *p = buf;
	int i;
	
	do
	{
		n = read(fd, l, kBufSize);
		
		for(i = 0; i < n; i++)
		{
			*p = l[i];
			if(p != buf && *p == 10 && *(p-1) == 13)
			{
				*(p-1) = 0;
				cline = 1;
				break;
			}
			p++;
		}
		*p = 0;
	} while(cline == 0 && n > 0);
	
}

int serverSetup(struct sockaddr_in* S,const int PORT,const int serverSocket){

	memset(S,0,sizeof(struct sockaddr_in));
	S->sin_family = AF_INET;
	S->sin_port = htons(PORT);
	S->sin_addr.s_addr = INADDR_ANY; /* listen for all incoming connection on configured port */

	if(bind(serverSocket,(struct sockaddr*)S,sizeof(*S)) < 0){ /* bind the socket to listen for data on a port */
		fprintf(stderr,"error: error while binding server to port %d\n\nIt is possible that a program is already using this port or the current server is shutting down.\n\n",PORT);
		return 1;
	}else{
		return 0;
	}
}

void printUserDAT(struct sockaddr_in* client){ /* Side in function call determines whether its written to server or user */

	system("clear");
	printf("Client information\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\n");

	printf("IP(hex):%x\nPort used:%d\n\n",ntohl(client->sin_addr.s_addr),ntohs(client->sin_port));
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

}	

int generateCMDcode(char* userDAT){

	int i,x;
	const char* NET = "NET-";
	const char* ROUTE = "ROUTE-";
/* Removing the support for automatic upper case for marks */
/* 	for (i = 0; i < strlen(userDAT); i++) 
	{
		userDAT[i] = toupper(userDAT[i]);
	} */

	if(0 == strcmp(userDAT,"QUIT") || 0 == strcmp(userDAT,"CLOSE")){
	
		return 0;
	}

	if(0 == strcmp(userDAT,"HELP")){
		return 3;
	}
	else{
		/* Logic to see if parent command NET or ROUTE is called and return with value specific to it */
		
		x = 0;
		for (i = 0; i < strlen(NET); i++)
		{
			if(userDAT[i]!=NET[i]){
				x = -1;
			}
			
		}
		if(x != -1){return 1;}
		else{
			x = 0;
			for (i = 0; i < strlen(ROUTE); i++){
				if(userDAT[i]!=ROUTE[i]){
					x = -1;
				}
			
			}
			if(x != -1){
				return 2;
			}
		}
		
	}
	return -1;

}

char * IDSTRING(int i){

	int counter = 0;
	int i_copy = i;
	char* string;

	while(i != 0){

		i/=10;
		counter++;

	}
	string = (char*)malloc((sizeof(char)*counter));
	sprintf(string,"%d\r\n",i_copy);
	printf("String in insertINT %s\n",string);


	return string;
}

char * ListNumStr(int i){

	int counter = 0;
	int i_copy = i;
	char* string;

	while(i != 0){

		i/=10;
		counter++;

	}
	string = (char*)malloc((sizeof(char)*counter)+(sizeof(char)*6));
	sprintf(string,"+OK %d\r\n",i_copy);
	


	return string;
}

char *JustNum(int i){

	int counter = 0;
	int i_copy = i;
	char* string;

	while(i != 0){

		i/=10;
		counter++;

	}
	string = (char*)malloc((sizeof(char)*counter));
	sprintf(string,"%d\r\n",i_copy);
	


	return string;

}

/* Net commands */

void NET_ADD(Graph* G, int fd, int ID){
	const char* success = "+OK Added\r\n";
	const char* failure = "-ERR Failure while adding server to graph. It either exists or another error occurred \r\n";
	char message[100];
	Node *N;
	Vertex*V;
	printf("\nCommand called: NET ADD\n");
	
	if(!G){
		printf("MAJOR ERROR: NO GRAPH HAS BEEN MADE!\n");
		write(fd,failure,strlen(failure));
	}

	N = G->head;

	while(N){
		V = N->data;
		if(V->id == ID){
			write(fd,failure,strlen(failure));
			return;
		}
		N = N->next;
	}

	if(add_vertex(G,ID)){
		sprintf(message,"+OK Added %d\r\n",ID);
		write(fd,message,strlen(message));
	}else{
		write(fd,failure,strlen(failure));
		return;
	}

}

void NET_DELETE(Graph* G,int fd,int ID){

	Node *N;
	Vertex*V;
	const char* success = "+OK success on deleting the server\r\n";
	const char* failure = "-ERR failure on deleting the server. It either doesnt exist or an error has occurred\r\n";
	int found = 0;
	char message[100];
	if(!G){
		printf("MAJOR ERROR: NO GRAPH HAS BEEN MADE!\n");
		write(fd,failure,strlen(failure));
		return;
	}

	N = G->head;

	while(N){
		V = N->data;

		if(V->id == ID){
			found = 1;
		}
		N = N->next;
	}
	if(!found){
		write(fd,failure,strlen(failure));
		return;
	}else{
		sprintf(message,"+OK Deleted %d\r\n",ID);
		write(fd,message,strlen(message));
		remove_vertex(G,ID);
	}

	printf("\nCommand called: NET DELETE\n");
}

void NET_LIST(Graph* G,int fd){

	Node*N;
	Vertex*V;
	const char * failure = "-ERR error while processing the graph of servers. Either no servers exist or there was another error.\r\n";
	char* IDSTR;
	int counter = 0;

	if(!G){
		printf("MAJOR ERROR: NO GRAPH HAS BEEN MADE!\n");
		write(fd,failure,strlen(failure));
		return;
	}

	N = G->head;
	
	while (N)
	{
		counter++;
		N = N->next;
	}
	if(counter <= 0){
		write(fd,failure,strlen(failure));
		return;
	}

	IDSTR = ListNumStr(counter);
	write(fd,IDSTR,strlen(IDSTR));
	free(IDSTR);
	N = G->head;

	while(N){

		V = N->data;

		IDSTR = IDSTRING(V->id);
		write(fd,IDSTR,strlen(IDSTR));
		free(IDSTR);

		N = N->next;
	}

	printf("\nCommand called: NET LIST\n");
}

void NET_COMMAND(char*userDAT,Graph*G,int fd){ /* Process the NET type command */

  const char* wrong_command = "-ERR Wrong NET command. Type HELP for a list of commands\r\n";
  const char* wrong_number  = "-ERR In the current command, you either didnt enter a number or an error has occurred\r\n";
  char * word;
  int i;

  word = strtok (userDAT," -");

  for(i = 0; i < 1; i++){
    word = strtok (NULL, " -");
  }

  if(0 == strcmp(word,"ADD")){

	word = strtok (NULL, " -");
	if(word){
		if(atoi(word) <=0){
			write(fd,wrong_number,strlen(wrong_number));
			return;
		}
		NET_ADD(G,fd,atoi(word));
	}
	else{
		write(fd,wrong_number,strlen(wrong_number));
		return;
	}

  }
  else if(0 == strcmp(word,"DELETE")){

	word = strtok (NULL, " -");
	if(word){
		if(atoi(word) <=0){
			write(fd,wrong_number,strlen(wrong_number));
			return;
		}
		NET_DELETE(G,fd,atoi(word));
	}
	else{
		write(fd,wrong_number,strlen(wrong_number));
		return;
	}
	

  }
  else if(0 == strcmp(word,"LIST")){
	  
	NET_LIST(G,fd);

  }
  else{
	  write(fd,wrong_command,strlen(wrong_command));
	  return;
  }

}

void ROUTE_COMMAND(char*userDAT,Graph*G, int fd){ /* Process the ROUTE type command */

	const char* wrong_command = "-ERR Wrong ROUTE command. Type HELP for a list of commands\r\n";
	const char* wrong_number  = "-ERR In the current command, you either didnt enter a number or an error has occurred\r\n";
	const char* wrong_ID      = "-ERR A network with one of the ID's you specified does not exist\r\n";
	const char* route_added   = "+OK Route added/Updated\r\n";
	const char* route_deleted = "+OK Route deleted\r\n";
	char * word,*word_copy;
	char *message;
	int i,edgecount;
	int routeparams[3];
	Vertex* A,*B,*V;
	Edge** E;
	Node *N;
	Path* P;
	int PENT;

	word = strtok (userDAT," -");

	for(i = 0; i < 1; i++){
		word = strtok (NULL, " -");
	}	
	/* ADD */
	if(0 == strcmp(word,"ADD")){
		word_copy = word;

		for(i = 0; i < 3 ;i++){
			word = strtok (NULL, " -");
			
			if(word == NULL){
				write(fd,wrong_number,strlen(wrong_number));
				return;
			}

			if(atoi(word) < 0 || word == NULL){

				write(fd,wrong_number,strlen(wrong_number));
				return;
			}

			routeparams[i] = atoi(word);
		}

		if(routeparams[0] == routeparams[1]){
			write(fd,wrong_number,strlen(wrong_number));
			return;
		}


		/* Check if either network exists (src, dest) */

		A = find_vertex(G,routeparams[0]);
		B = find_vertex(G,routeparams[1]);

		if(!A||!B){
			write(fd,wrong_ID,strlen(wrong_ID));
			return;
		}

		

		/* Check if route already exists */

		E = get_edges(G,A,&edgecount);
		for(i = 0; i < edgecount; i++){

			if(edge_destination(E[i])==routeparams[1] || edge_destination(E[i])==routeparams[0] ){
				printf("ROUTE HERE ALREADY EXISTS\n");
				E[i]->weight = (double)routeparams[2];
			}

		}
		edgecount = 0;
		E = get_edges(G,B,&edgecount);
		for(i = 0; i < edgecount; i++){

			if(edge_destination(E[i])==routeparams[1] || edge_destination(E[i])==routeparams[0] ){
				printf("ROUTE HERE ALREADY EXISTS\n");
				E[i]->weight = (double)routeparams[2];
			}

		}

		/* Check if route already exists */

		write(fd,route_added,strlen(route_added));
		add_edge_undirected(G,routeparams[0],routeparams[1],(double)routeparams[2]);


	}
	/* ADD */

	/* DELETE */
	else if(0 == strcmp(word,"DELETE")){

		for(i = 0; i < 2 ;i++){
			word = strtok (NULL, " -");
			
			if(word == NULL){
				write(fd,wrong_number,strlen(wrong_number));
				return;
			}

			if(atoi(word) < 0 || word == NULL){

				write(fd,wrong_number,strlen(wrong_number));
				return;
			}

			routeparams[i] = atoi(word);
		}

		if(routeparams[0] == routeparams[1]){
			write(fd,wrong_number,strlen(wrong_number));
			return;
		}

		A = find_vertex(G,routeparams[0]);
		B = find_vertex(G,routeparams[1]);

		if(!A||!B){
			write(fd,wrong_ID,strlen(wrong_ID));
			return;
		}

			write(fd,route_deleted,strlen(route_deleted));
			remove_edge(G,routeparams[0],routeparams[1]);
			remove_edge(G,routeparams[1],routeparams[0]);
		}
	/* DELETE */
	else if(0==strcmp(word,"SHOW")){
		/* +OK 6
		would indicate that details of six links will follow. Following this line, the network IDs for the other
		end of the link should be sent to the client, one per line.
		This command should return an error response if the network does not exist.
 */
		/* N = G->head; */
		word = strtok (NULL," -");

		if(!word){
			write(fd,wrong_number,strlen(wrong_number));
			return;
		}

		printf("Word is %d\n",word);
		if(!(V = find_vertex(G,atoi(word)))){
			printf("V ERROR\n");
			write(fd,wrong_number,strlen(wrong_number));
			return;
		}
		else{
			if(!word){
				write(fd,wrong_number,strlen(wrong_number));
				return;
			}
			E = get_edges(G,V,&edgecount);
			message = ListNumStr(edgecount);
			write(fd,message,strlen(message));
			free(message);
			
			for(i = 0; i < edgecount; i++){
				
				message = JustNum(edge_destination(E[i]));
				write(fd,message,strlen(message));
				free(message);

			}
		}
/* 		V = find_vertex()
 */
	
	}

	else if(0==strcmp(word,"HOP")){

/*  
	Receipt of this command should cause the server to query the graph and return the next hop
where a packet should be sent to forward it from the source network to the destination network.
The networks are specified using their integer IDs. Your server should run Dijkstra’s algorithm on its
graph and return the next-hop for the specified network, or -1 if there’s no possible route between
the two networks.
The program should respond indicating a success, following the ‘+OK’ with the network ID of the
next hop (i.e. the network to which this packet should be sent). An error should only be returned if
either of the networks does not exist, or if the source and destination networks are identical. 

*/

		for(i = 0; i < 2;i++){
			word = strtok (NULL, " -");
			
			if(word == NULL){
				write(fd,wrong_number,strlen(wrong_number));
				return;
			}

			if(atoi(word) < 0 || word == NULL){

				write(fd,wrong_number,strlen(wrong_number));
				return;
			}

			routeparams[i] = atoi(word);
		}

		if(!(P = dijkstra(G,routeparams[0],&PENT))){
			write(fd,wrong_ID,strlen(wrong_ID));
			return;
		}
		
		if(!(V = find_vertex(G,routeparams[0]))){
			write(fd,wrong_ID,strlen(wrong_ID));
			return;
		}
		else if(!(V = find_vertex(G,routeparams[1]))){
			write(fd,wrong_ID,strlen(wrong_ID));
			return;
		}
		
		write(fd,"+OK\r\n",sizeof(char)*5);
		i = P[routeparams[1]].next_hop;
		message = JustNum(i);
		write(fd,message,strlen(message));

	}

	else if(0==strcmp(word,"TABLE")){
		
	}
	else{
	  write(fd,wrong_command,strlen(wrong_command));
	  return;
  	}
    

/*  */


}

void ServerConnection(int fd,Graph*G){

	const char responses[6][2048] = {
		"+OK Established connection to server|\n\nType HELP for a list of commands\n\r\n",
		"-ERR Unknown/invalid command\r\n",
		"+OK closing connection to server....\nConnection closed!\r\n",
		"+OK Parent command (NET)\r\n",
		"+OK Parent command (ROUTE)\r\n",
		"+INFO |\n\nQUIT - Closes connection between you and the server\n\nHELP - shows this screen\n\
		\n\tROUTE:\n\n\t \
		ROUTE-ADD [src network] [dest network] [weight]\
		\n\t\t\t- Adds new server to the dictionary of servers.\n\t\t\tSRC -> DEST explains the route between the current server and the added server, weight is the cost of travelling to the other server\
		\n\n\t\t\tROUTE-DELETE [server ID]\
		\n\t\t\t- Deletes server with specified ID\
		\n\n\t\t\tROUTE-SHOW [network]\
		\n\t\t\t- This lists all the IDS of the servers added to the dictionary of servers\
		\n\n\t\t\tROUTE-HOP [src network] [dest network]\
		\n\t\t\t- Queries the dictionary of networks for the shortest route to the dest network\
		\n\n\t\t\tROUTE-TABLE [network] \
		\n\t\t\t- Shows all the possible routes for each network from the current server\
		\n\n\tNET:\
		\n\n\t\t\tNET-ADD [network ID]\
		\n\t\t\t- Adds a server to the dictionary of servers (this is different from ROUTE-ADD since this adds a dormant server thats not connected to anything else) \
		\n\n\t\t\tNET-DELETE\
		\n\t\t\t- Deletes a server fromt he dictionary of servers\
		\n\n\t\t\tNET-LIST\
		\n\t\t\t- lists all the servers in the dictionary, including the non connected ones (dormant servers), unlike ROUTE-LIST\n\n\r\n",
	};

	char outBuffer[512];
	char inputBuffer[512], *p;
	int state = TAKING_INPUT,code;

	write(fd,responses[0],strlen(responses[0]));
	printf("User connected to server!\n");
	
	while(state != CLOSING_CONNECTION){	/* Need to fix getting user input */

		ReadLineFromNetwork(fd,inputBuffer,512); /* No need for checking if message exceeds 512 since PDF said to assume the messages are under */
		
		switch (code = generateCMDcode(inputBuffer))
		{
		case 0:
			printf("command code: %d\n",code);
			printf("InputBuffer: %s\n",inputBuffer);
			write(fd,responses[2],strlen(responses[2]));
			state = CLOSING_CONNECTION;
			break;
		case 1:
			printf("command code: %d\n",code);
			printf("InputBuffer: %s\n",inputBuffer);
			/* write(fd,responses[3],strlen(responses[3])); */
			NET_COMMAND(inputBuffer,G,fd);

			break;
		case 2:
			printf("command code: %d\n",code);
			printf("InputBuffer: %s\n",inputBuffer);
			/* write(fd,responses[4],strlen(responses[4])); */
			ROUTE_COMMAND(inputBuffer,G,fd);
			break;
		case 3:
			printf("command code: %d\n",code);
			printf("InputBuffer: %s\n",inputBuffer);
			write(fd,responses[5],strlen(responses[5]));	
			break;
		default:
			printf("command code: %d\n",code);
			printf("InputBuffer: %s\n",inputBuffer);
			write(fd,responses[1],strlen(responses[1]));
			break;
		}
		
		
	}

	printf("Connection closed...\n");
	
}

int main(int argc, const char * argv[])
{
	int serverSocket = -1,clientConnection,PORT;
	unsigned int alen;
	struct sockaddr_in server,client;
	Graph* graph = initialise_linked_list();


	/* Checks */
	if(argc != 2){
		fprintf(stderr,"error: expected 1 command line argument but got %d\nExpected ./server [PORT]",argc-1);
		return 1;
	}
	
	if((PORT = atoi(argv[1])) == 0){
		fprintf(stderr,"error: either 0 or an invalid port number was entered\n");
		return 1;
	}

	if(!(serverSocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))){
		fprintf(stderr, "error: couldnt initalise server\n");
		return 1;
	}

	if(serverSetup(&server,PORT,serverSocket)){
		return 1;
	}

	if(listen(serverSocket,15) < 0){
		fprintf(stderr, "error: couldnt complete listening function\n");
		return 1;
	}
	/* Checks */

	while(1){
		printf("Awaiting new connection...\n");
		alen = sizeof(client);
		clientConnection = accept(serverSocket,(struct sockaddr*)&client,&alen);
		
		ServerConnection(clientConnection,graph);

		close(clientConnection);
	}

	free(graph);

	return 0;
}


/* Code notes:

	socket: opens a TCP connection <- according to man page

	According to https://stackoverflow.com/questions/6729366/what-is-the-difference-between-af-inet-and-pf-inet-in-socket-programming, PF_INET and AF_INET are identical
	seems the convention is for AF = client | PF = server. We also use this for IPV4 connection

	AF_INET: an address family that is used to designate the type of addresses that your socket can communicate with

	SOCK_STREAM: a good way to ensure a viable TCP connection. UDP would be SOCK_DGRAM

	IPPROTO_TCP: ensuring we are using TCP and not UDP

	bind: bind a name to a socket - man page | int bind(int socket, const struct sockaddr *address,socklen_t address_len);

	bind info: bind a socket to a port for listening purposes

	listen(): tell OS to listen for incoming connections

	accept: does the actual listening part. it accepts a connection and does processing.

	accept info: param1(what the server is), param2(a pointer to a sockaddr variable, to edit its data so it can say the IP and other information

	accept info 2: param3(how much data is in the client pointer). accept returns a socket(integer value) for storing so we can store the client data

	Use this to communicate with server: nc 127.0.0.1 4242 -CN

	nhtol vs nhtos (l = 32 bit value parsing | s = 16 bit value parsing) AKA long vs short parsing

	close(): closes established connection

 */

/* ROUTE-DELETE <src network> <dest network>
Receipt of this command from the client should cause the server to delete the specified link
between two networks from the graph. The IDs for the networks are specified by the integer
parameter.
The server should respond appropriately to indicate success after deleting the network from the
graph. If the link does not exist, then the server should respond with an error and the graph should
not be altered.

This command should return an error response if the network does not exist.
ROUTE-HOP <src network> <dest network>
Receipt of this command should cause the server to query the graph and return the next hop
where a packet should be sent to forward it from the source network to the destination network.
The networks are specified using their integer IDs. Your server should run Dijkstra’s algorithm on its
graph and return the next-hop for the specified network, or -1 if there’s no possible route between
the two networks.
The program should respond indicating a success, following the ‘+OK’ with the network ID of the
next hop (i.e. the network to which this packet should be sent). An error should only be returned if
either of the networks does not exist, or if the source and destination networks are identical.

ROUTE-TABLE <network>
Receipt of this command should cause the server to list the complete routing table for the
specified network. The networks is specified using its integer IDs. Your server should run Dijkstra’s
algorithm on its graph and return the next-hop for every other network in the graph (i.e. no route is
shown for the specified network).
The server will respond with a success response containing the ‘+OK’ followed by the number of
entries in the routing table, e.g.:
+OK 6
This should then be followed by a line for each entry of the routing table (excluding the network
specified), in the following format:
<current> -> <destination>, next-hop <hop>, weight <weight>
where <current> is the integer ID for the network being queried, and <destination> is the
network ID of the destination network. <hop> is the network ID where packets should be sent to
reach the <destination> network (this may, or may not, be the same network), while <weight>
should be the cost of traversing that route (as calculated by Dijkstra’s algorithm).
If there is no route to a network, <hop> should be -1 and <weight> should read INF.



 */


/* code graveyard

char* intINString(char* string, int number){



	int digitAmount,numCopy;
	char *outputStr;
	int length,i;
	char L_SIDE[500];
	char R_SIDE[500];

	
	
	digitAmount = 0;
	numCopy = number;

	while(number != 0){

		number/=10;
		digitAmount++;

	}

	outputStr = (char*)malloc( (sizeof(char)*strlen(string)-2)+ (sizeof(char)*digitAmount)+(sizeof(char)*2)); 

	for(i = 0; i < strlen(string); i++){

		if(string[i] == '{'){break;}
		else{L_SIDE[i] = string[i];}		
	}

	L_SIDE[i] = '#'; 
	
	for(i = i+2; i < strlen(string); i++){

		R_SIDE[i] = string[i];

	}
	R_SIDE[i+1] = '#';



	length = strlen(string)-2 + digitAmount + 2;



	return NULL;

}

code graveyard */