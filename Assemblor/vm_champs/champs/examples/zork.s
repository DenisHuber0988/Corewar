.name "zork"
.comment "I'M ALIIIIVE"


infi:	sti	r1,%:l0,%1
		sti	r1,%:l1,%1
		sti	r1,%:l2,%1
		sti	r1,%:l3,%1
		sti	r1,%:l4,%1
		sti	r1,%:l5,%1
		sti	r1,%:l6,%1
		sti	r1,%:l7,%1
		sti	r1,%:l8,%1
		sti	r1,%:l9,%1
		sti	r1,%:l10,%1

l0:		live	%1
l1:		live	%1
l2:		live	%1
l3:		live	%1
l4:		live	%1
l5:		live	%1
l6:		live	%1
l7:		live	%1
l8:		live	%1
l9:		live	%1
l10:	live	%1
		zjmp	%:l0

topd:	ld		%9,r3
		sti		r3,%:fin,%-6
		ld		%2,r3
		sti		r3,%:fin,%-16
		ld		%0,r3
		zjmp	%:infi

fin:	live	%633
