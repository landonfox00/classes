
% problem 1a

isSet( [] ).
isSet( [ H | T ] ) :-
	not( member( H, T ) ),
	isSet( T ).


% problem 1b
% assuming we do not need to check if set

subset( [], _ ).
subset( [ H | T ], S ) :-
	member( H, S ),
	subset( T, S ).


% problem 1c

union( [], B, C ) :-
	subset( B, C ),
	subset( C, B ).
union( [ H | T ], B, C ) :-
	D = [ H | B ],
	union( T, D, C ).


% problem 1d

intersection( [], _, [] ).
intersection( [ H1 | T1 ], B, [ H2 | T2 ] ) :-
	member( H1, B ),
	H1 = H2,
	intersection( T1, B, T2 ).
intersection( [ _ | T ], B, C ) :-
	intersection( T, B, C ).


% problem 2

tally( _, [], 0 ).
tally( E, [ E | T ], N ) :-
    tally( E, T, M ),
	N is M + 1.
tally( E, [ _ | T ], N ) :-
	tally( E, T, N ).


% problem 3

subst( _, _, [], [] ).
subst( X, Y, [ X | T1 ], [ Y | T2 ] ) :-
	subst( X, Y, T1, T2 ).
subst( X, Y, [ H | T1 ], [ H | T2 ] ) :-
	subst( X, Y, T1, T2 ).


% problem 4

insert( 1.0Inf, L, L ).
insert( X, [], [ X ] ) :-
	X < 1.0Inf.
insert( X, [ H | T1 ], [ X, H | T2 ] ) :-
	X =< H,
	insert( 1.0Inf, T1, T2 ).
insert( X, [ H | T1 ], [ H | T2 ] ) :-
	insert( X, T1, T2 ).


% problem 5

flatten( [], [] ).
flatten( [ H | T ], B ) :-
	flatten( H, C ),
	flatten( T, D ),
	append( C, D, B ).
flatten( H, [ H ] ).
