.name "Liquid Dante"
.comment "Say What ?"

daddy_prep:
live	%3134197165
st              r1, -4
ld      %151121408, r2
st      r2, -511
ld      %151053056, r2
st      r2, -24
st              r1, 340
st              r1, 215
ld      %47186254, r2
st      r2, -17
ld      %17367239, r2
st      r2, -25

#Load des registres qui serviront à zjmp
ld      %151037440, r15
ld      %151038720, r13
ld      %151040000, r10

#Preparation du st r3 à 511
ld      %57672449, r2
ld      %4278415363, r3
ld      %33489776, r4
ld      %50462467, r5
ld      %1879245311, r6
#ld      %57672705, r2
#ld      %57672449, r3
#ld      %57672961, r4
#ld      %57673217, r5
#ld      %57673473, r6

ld      %57673729, r7
ld      %57673985, r8
ld      %57674241, r9
ld      %57674753, r11
ld      %57675009, r12
ld      %57675521, r14
ld      %0, r16
st              r1, 284
zjmp    %:mach_1

faire_le_plein:

aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16



daddy_shake:
ld		-20, r16
ld		-30, r16
ld		-40, r16
live	%3134197165
zjmp	%-110
ld      -4, r4
ld      -13, r15
fork    %:c2
fork    %:c4
ld		%16, r3
ld		%0, r16
ld		%0, r16
zjmp	%:daddys_twerk

c2:
fork	%:c3
ld		%12, r3
st      r15, r4
ld		%0, r16
zjmp	%:daddys_twerk

c3:
ld		%8, r3
ld      %4288348160, r4
ld		%0, r16
zjmp	%:daddys_twerk

c4:
ld		%4, r3
ld      %190317571, r4
ld		%0, r16
zjmp	%:daddys_twerk

daddys_twerk:
live	%3134197165
sti		r4, r3, %-509
zjmp    %-511

faire_le_vide:
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16
aff     r16

mach_1:
live	%3134197165
ld              %57672193, r16
st              r2, 511
st              r3, 510
st              r4, 509
st              r5, 508
st              r6, 507
st              r2, 506
st              r3, 505
st              r4, 504
st              r5, 503
st              r6, 502
st              r16, 501
st              r3, 500
st              r4, 499
st              r5, 498
st              r6, 497
st              r2, 496
st              r3, 495
st              r4, 494
st              r5, 493
st              r6, 492


ld              %33489776, r2
ld              %57672193, r4
st              r7, 477
st              r2, 475
st              r11, 472
st              r2, 470
st              r14, 467
st              r2, 465
ld              %151101440, r2
st              r2, 455

ld      %57672705, r2
ld      %57672961, r4
ld      %57673217, r5
ld      %151125760, r6

#r3 ne fera que se répliquer lui même
ld              %57672449, r3

ld              %0, r16

top:
zjmp    %313

