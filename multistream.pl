#!/usr/bin/perl -w

use strict;
use Socket;
$|=1;

socket(LISTEN_SOCKET,AF_INET,SOCK_STREAM,getprotobyname('tcp'));
setsockopt(LISTEN_SOCKET,SOL_SOCKET,SO_REUSEADDR,pack("l",1));
bind(LISTEN_SOCKET,sockaddr_in(5554,INADDR_ANY));

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
