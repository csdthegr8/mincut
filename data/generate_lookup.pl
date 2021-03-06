use strict;
use Math::Combinatorics;

my @n = qw { U D L R };

foreach my $i (2 .. 10) {
    my $combinat = Math::Combinatorics->new (
	count => $i,
	data => [@n],
	);

    while(my @combo = $combinat->next_combination){
	print join(' ', @combo)."\n";
    }
}


