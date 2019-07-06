#!/usr/bin/perl
use strict;
use Time::HiRes qw/sleep/;
use feature 'say';

my $lock="lock";
my $input="input.txt";
my $n=10;
my $waitTime=0.2;

while(1){
    if( system("mkdir $lock &> /dev/null") ){
        say "wait...";
        sleep $waitTime;
        next;
    }

    my @list= split("\n", `head -n $n $input`);

    `sed -i -e '1,${n}d' $input`;

    `rmdir $lock`;

    if( int @list == 0 ){ last; }

    foreach my $line (@list){
        unless( $line =~ /\S/ ){ next; }
        chomp $line;
        $line =~ s/(^")|("$)//g;

        my @cmd_parts = ();
        push( @cmd_parts, 'curl -s' );
        push( @cmd_parts, '-X DELETE' );
        push( @cmd_parts, "'http://xxx.xxx.xxx.xxx/$line'" );

        my $cmd = join( " ", @cmd_parts);
        my $result = `$cmd`;
        say $cmd;

    }

sleep 5;
}
