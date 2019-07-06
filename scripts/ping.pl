#!/usr/bin/perl
use Net::Ping;
my $host = 'ksknet.net';
my $p = Net::Ping->new("icmp");

my $result = $p->ping($host, 2);
if($result){
	print "$host is alive!\n";
}
