dir=cc/poub/champs
#dir=~/ASM_Corewar_tests

rm $dir/*.cor
for file in $dir/*.s;
do
	echo "==> $file <=="
	valgrind ./asm $file 2>> test1
	echo ""
	echo ""
done
