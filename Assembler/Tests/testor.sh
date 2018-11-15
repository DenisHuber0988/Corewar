dir=vm_champs/champs
#dir=~/ASM_Corewar_tests

rm $dir/*.cor
rm $dir/*.tor
for file in $dir/full.s;
do
	echo "==> $file <=="
	./testasm $file 2>> test2
	./asm $file 2>> test1
	echo ""
	echo ""
done
