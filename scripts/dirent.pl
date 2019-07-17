use IO::Dirent;

opendir DIR, "/usr/local/foo";
my @entries = readdirent(DIR);
closedir DIR;

print $entries[0]->{name}, "\n";
print $entries[0]->{type}, "\n";
print $entries[0]->{inode}, "\n";

opendir DIR, "/etc";
while( my $entry = nextdirent(DIR) ) {
  print $entry->{name} . "\n";
}
closedir DIR;
