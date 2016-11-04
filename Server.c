#include<stdio.h>
#include<string.h> //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h> //write
#include<time.h>
int main(int argc , char *argv[])
{
int socket_desc , new_socket , c;
struct sockaddr_in server , client;
char *message,client_message[2000],str[4];
int read_size;
int i , p , num ;
int no[10],Ans[10];
int guess[4],int_guess ;
int tmp , counterA , counterB , j , k ;
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8888 );
//Bind
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("bind failed");
return 1;
}
puts("bind done");
//Listen
listen(socket_desc , 3);
//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
if (new_socket<0)
{
perror("accept failed");
return 1;
}
puts("Connection accepted");
for ( i = 0 ; i < 10 ; ++i )
no[i] = i;
srand(time(NULL)) ;
for ( i = 0 ; i < 4 ; ++i ) {
p = rand() % 10 ;
if ( p == i ) continue ;
tmp = no[i] ;
no[i] = no[p] ;
no[p] = tmp ;}
printf("%d%d%d%d\n",no[3],no[2],no[1],no[0]);
//Reply to the client
while(1)
{
bzero(str,4);
read(new_socket,str,4);
int_guess=(str[0]-'0')*1000+(str[1]-'0')*100+(str[2]-'0')*10+(str[3]-'0')*1;
guess[3] = int_guess / 1000 ;
guess[2] = ( int_guess / 100 ) % 10 ;
guess[1] = ( int_guess / 10 ) % 10 ;
guess[0] = int_guess% 10 ;
counterA = counterB = 0;
for( j = 0 ; j < 4 ; ++j )
	for( k = 0 ; k < 4 ; ++k )
		if( no[j] == guess[k] )
			if( j == k )
				counterA++;
			else
				counterB++;
if( counterA == 4 )
{
message="Right number!!\n";
write(new_socket,message,strlen(message));
return 1;
}
else
{
sprintf(client_message,"Hint: %dA%dB\n",counterA,counterB);
write(new_socket,client_message,strlen(client_message));
counterA=0;
counterB=0;
}
}

return 0;}
