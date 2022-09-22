This is a simple client-server application. Upon execution, the client prints a menu of possible commands, and prompts the user to enter the number of a command which should be executed on the server. Then, the client sends the number to the server (which is waiting to read requests on a predefined UDP port). The server  reads the number from the client and execute the appropriate command, returning the results (as a string) to the client. The client prints the reply to the console and is ready to accept additional commands from the user.

The commands that are available are:
1. Current time in UTC
2. PID (process ID) of the server
3. Random number between 1 and 50, inclusive

The Application Layer Protocol is clearly defined, and exchanges data in ASCII format only. The server is connectionless and iterative, i.e. only process one request at a time (see net1/server.c). 
