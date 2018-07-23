.name			"42"
.comment		"Just a basic Winner Program"


entree:	live	%42		# entree
		live	%-42		# entree
		live	%:tir		# entree
		ld	%2, r2
		ld	2,r2
		ld	%:tir,r2
		ld	:tir,r2
		st	r3,3
		st	r3,3
		st	r3,:tir
		st	r3,:tir
		st	r3,r3
		add	r4,r4,r4		#3
		sub	r5,r5,r5		#3
		and	r6,r6,r6		#3
		and	%6,6,r6			#3
		and	:tir,%:tir,r6	#3
		and	%:tir,:tir,r6	#3
		and	6,:tir,r6		#3
		or	r7,r7,r7		#3
		or	%7,7,r7			#3
		or	:tir,%:tir,r7	#3
		or	%:tir,:tir,r7	#3
		or	7,:tir,r7		#3
		xor	r8,r8,r8		#3
		xor	%8,8,r8			#3
		xor	:tir,%:tir,r8	#3
		xor	%:tir,:tir,r8	#3
		xor	8,:tir,r8		#3
		zjmp	%:tir			#1
		zjmp	%9			#1
		ldi		r10,r10,r10
		ldi		%10,%10,r10
		ldi		%:tir,%:tir,r10
		ldi		:tir,%10,r10
		ldi		10,r10,r10
		sti		r11,r11,r11			#3
		sti		r11,11,r11			#3
		sti		r11,%11,%11			#3
		sti		r11,:tir,%:tir			#3
		sti		r11,%:tir,%:tir			#3
		fork	%12			#1
		fork	%:tir			#1
		fork	%12			#1
		fork	%:tir			#1
		lld		%13,r13			#2
		lld		%:tir,r13			#2
		lld		13,r13			#2
		lld		:tir,r13			#2
		lldi	14,r14,r14			#3
		lldi	14,%14,r14			#3
		lldi	:tir,%:tir,r14			#3
		lldi	%:tir,r14,r14			#3
		lfork	%:tir			#1
		lfork	%:tir			#1
		lfork	%15			#1
		lfork	%15			#1

tir:
		aff		r16			#1
