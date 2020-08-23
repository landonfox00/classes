
; problem 1: returns an identical list except for every occurrence of x has been replaced with y
( define ( subst x y L )
	( if ( null? L )
		L
		( cons
			( if ( eq? ( car L ) x )
				y
				( car L )
			)
			( subst x y ( cdr L ) )
		)
	)
)

; problem 2: determines if a list has unique elements
( define ( all-different? L )
	( cond
		[ ( null? ( cdr L ) ) #t ]
		[ ( eqv? ( car L ) ( car ( cdr L ) ) ) #f ]
		[ else
			( and
				( all-different? ( cons ( car L ) ( cdr ( cdr L ) ) ) )
				( all-different? ( cdr L ) )
			)
		]
	)
)

; problem 3:
( define Tree
	'( 13
		( 5
			( 1
				()
				()
			)
			( 8
				()
				( 9
					()
					()
				)
			)
		) 
		( 22
			( 17
				()
				()
			)
			( 25
				()
				()
			)
		)
	)
)

( define ( val T )
	( car T )
)

( define ( left T )
	( car ( cdr T ) )
)

( define ( right T )
	( car ( cdr ( cdr T ) ) )
)

; problem 3a: returns number of nodes in tree
( define ( n-nodes T )
	( cond
		[ ( null? T )  0 ]
		[ ( and ( null? ( left T ) ) ( null? ( right T ) ) ) 1 ]
		[ ( null? ( left T ) ) ( + 1 ( n-nodes ( right T ) ) ) ]
		[ ( null? ( right T ) ) ( + 1 ( n-nodes ( left T ) ) ) ]
		[ else
			( +
				1
				( n-nodes ( left T ) )
				( n-nodes ( right T ) )
			)
		]
	)
)

; problem 3b: returns the number of leaves in tree
( define ( n-leaves T )
	( cond
		[ ( null? T )  0 ]
		[ ( and ( null? ( left T ) ) ( null? ( right T ) ) ) 1 ]
		[ ( null? ( left T ) ) ( n-leaves ( right T ) ) ]
		[ ( null? ( right T ) ) ( n-leaves ( left T ) ) ]
		[ else
			( +
				( n-leaves ( left T ) )
				( n-leaves ( right T ) )
			)
		]
	)
)

; problem 3c: returns the height of the tree
( define ( height T )
	( cond
		[ ( null? T )  0 ]
		[ ( and ( null? ( left T ) ) ( null? ( right T ) ) ) 1 ]
		[ ( null? ( left T ) ) ( + 1 ( height ( right T ) ) ) ]
		[ ( null? ( right T ) ) ( + 1 ( height ( left T ) ) ) ]
		[
			( >
				( height ( left T ) )
				( height ( right T ) )
			)
				( + 1 ( height ( left T ) ) )
		]
		[ else
			( + 1 ( height ( right T ) ) )
		]
	)
)

; problem 3d: return postorder traversal of tree
( define ( postorder T )
	( append
		( if ( null? ( left T ) )
			'()
			( postorder ( left T ) )
		)
		( if ( null? ( right T ) )
			'()
			( postorder ( right T ) )
		)
		( list ( val T ) )
	)
)

; problem 4: returns all elements in list including sublists
( define ( flatten L )
	( if ( null? L )
		L
		( append
			( if ( list? ( car L ) )
				( flatten ( car L ) )
				( list ( car L ) )
			)
			( flatten ( cdr L ) )
		)
	)
)

; problem 5: determines if element is a member of bst
( define ( member-bst? V T )
	( cond
		[ ( null? T ) #f ]
		[ ( eqv? V ( val T ) ) #t ]
		[ ( < V ( val T ) ) ( member-bst? V ( left T ) ) ]
		[ ( > V ( val T ) ) ( member-bst? V ( right T ) ) ]
	)
)
