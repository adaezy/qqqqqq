This is a simple client-server application. Upon execution, the client should print a menu of possible commands, and prompt the user to enter the number of a command which should be executed on the server. Then, the client should send the number to the server (which is waiting to read requests on a predefined UDP port). The server should read the number from the client and execute the appropriate command, returning the results (as a string) to the client. The client should print the reply to the console and then be ready to accept additional commands from the user.

The command that should be available are:
1. Current time in UTC
2. PID (process ID) of the server
3. Random number between 1 and 50, inclusive

The Application Layer Protocol should be clearly defined, and must exchange data in ASCII format only. The server should be connectionless and iterative, i.e. only process one request at a time (see net1/server.c). Don't worry about making the communication reliable, e.g. by adding timeouts, etc.
