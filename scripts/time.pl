# print the time line on top
my $time = $firsttime;
my $step = ($maxtime - $firsttime) / 15;
while ($time < $maxtime) {
	my $s3 = ($time - $firsttime) * $mult;
	my $tm = int($time * 100) / 100.0;
	print "<text transform=\"translate($s3,89) rotate(90)\">$tm</text>\n";
	$time = $time + $step;
}

print "</svg>\n";
