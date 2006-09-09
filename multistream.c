#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* use strict;
use Socket;
$|=1; */

int main (int argc, char * argv[]) {

 int LISTEN_SOCKET;
 int result;
 int reuse_addr=1;
 struct sockaddr name;

 LISTEN_SOCKET = socket(AF_INET,SOCK_STREAM,getprotobyname('tcp'));
 if (LISTEN_SOCKET == -1) { perror("Creating socket: "); exit(1); }

 result = setsockopt(LISTEN_SOCKET,SOL_SOCKET,SO_REUSEADDR,
                   &reuse_addr,sizeof(reuse_addr));
 if (result == -1) { perror("Setting socket options: "); exit(1); }

 name.sa_len = 4;
 name.sa_family = AF_INET;
 name.sa_data
 result = bind(LISTEN_SOCKET,sockaddr_in(5554,INADDR_ANY));

listen(LISTEN_SOCKET,SOMAXCONN);

my $other_addr;
my $fd;
my $rin;
my $rout;
my $eout;
my %file_descriptors = (fileno(LISTEN_SOCKET) => *LISTEN_SOCKET{IO});
my ($nfound,$timeleft);
while ($other_addr = accept(CLIENT,LISTEN_SOCKET)) {
   print "Accepted a connection\n";
   print CLIENT "Hello there!\n"; 
   $file_descriptors{fileno(CLIENT)} = *CLIENT{IO};
   $rin = "";
   foreach $fd (keys %file_descriptors) { vec($rin,$fd,1) = 1; }
   ($nfound,$timeleft) = select ($rout=$rin,"",$eout=$rin,undef);
}
