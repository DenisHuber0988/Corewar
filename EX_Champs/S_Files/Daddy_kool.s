.name "Daddy_Kool_and_the_Gang"
.comment "
She is crazy like a fool...
What about it Daddy cool?

What you gonna do? You wanna get down?
Tell me, what you gonna do? Do you wanna get down?

She is crazy like a fool..
What about it Daddy cool?

Get down on it, get down on it, come on and
Get down on it, get down on it

I'm crazy like a fool!
What about it Daddy Cool?

How you gonna do it if you really don't want to dance
By standing on the wall?

Daddy...Daddy Cool !

How you gonna do it if you really don't wanna dance
By standing on the wall, get your back up off the wall
'Cause I heard all the people sayin'

Daddy...Daddy Cool !

Get down on it, come on and
Get down on it, if you really want it
Get down on it, you gotta feel it
Get down on it, get down on it

Daddy...Daddy Cool !

Get down on it, come on and 
Get down on it, baby, baby
Get down on it, get on it
Get down on it

Daddy...Daddy Cool ! 

I say people, what? What you gonna do?
You've gotta get on the groove
If you want your body to move, tell me, baby

She is crazy about her Daddy.
Oh...
She believes in him !
She loves her Daddy!"

daddy_shake:
ld				%3134197165,r2
st				r2, r3
st              r1, 6
live	%3134197165
fork    %:crazy_daddy
st				r1, 26
st				r1, 126
st				r1, 266
fork	%:dad_alive
ld		%0, r16    

daddy_move:
live	%3134197165
#LINE1
st		r2, -357
st		r2, -359
st		r2, -351
st		r2, -355
st		r2, -350
st		r2, -352
st		r2, -88
st		r2, -97
st		r2, -154
st		r2, -163
#LINE 2
st		r2, -344
st		r2, -344
st		r2, -340
st		r2, -340
st		r2, -337
st		r2, -337
st		r2, -202
st		r2, -211
st		r2, -268
st		r2, -277
live	%3134197165
#LINE 3
st		r2, -336
st		r2, -335
st		r2, -332
st		r2, -332
st		r2, -329
st		r2, -328
st		r2, -321
st		r2, -330
st		r2, -387
st		r2, -396
#LINE 4
st		r2, -322
st		r2, -321
st		r2, -318
st		r2, -318
st		r2, -315
st		r2, -314
st		r2, -435
st		r2, -444
st		r2, -501
st		r2, -510
#line 5
st		r2, -309
st		r2, -310
st		r2, -305
st		r2, -305
st		r2, -302
st		r2, -303
st		r2, -299
st		r2, -352
live	%3134197165
zjmp	%:daddy_move

dad_alive:
st	    r1, 6	
live	%3134197165
fork    %:crazy_daddy
st	    r1, 19
st	    r1, 6
born_to_be_cool:
live	%3134197165
zjmp	%:born_to_be_cool

daddy_cool:
live	%3134197165
fork    %:crazy_daddy
ld %68, r15
aff r15
ld %97, r15
aff r15
ld %100, r15
aff r15
ld %100, r15
aff r15
ld %121, r15
aff r15
ld %67, r15
aff r15
ld %111, r15
aff r15
ld %111, r15
aff r15
ld %108, r15
aff r15
ld %0, r15
aff r15
fork    %:born_to_be_cool
zjmp    %:daddy_cool

crazy_daddy:
st		r1, 6
live    %4320423
ld		%18, r3
ld		%406,r2
fork	%:booty_shake_2

booty_shake:
ld				%34144657, r4
st				r4, r5
st				r5, r6
ld				%50921485, r7
st				r7, r8
st				r7, r9
st				r7, r10
st				r7, r11
st				r7, r12
st				r7, r13
st				r7, r14
ld              %150994944, r15
ld				%4, r1
ld              %0, r16
ld              %0, r16
zjmp            %:daddys_twerk

booty_shake_2:
ld		%190055681, r4
ld		%190055937, r5
ld		%190056193, r6
ld		%190056449, r7
ld		%190056705, r8
ld		%190056961, r9
ld		%190057217, r10
ld		%190057473, r11
ld		%190057729, r12
ld		%190057985, r13
ld		%190058241, r14
ld		%167723008, r15
st		r1, 16
ld		%0, r1
zjmp	%:daddys_twerk


daddys_twerk:
live	%3134197165
sti		r4, r1, %448
zjmp    %442
