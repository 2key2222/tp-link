dirs=`find . -maxdepth 1 -type d`

for i in `seq 0 9`
do
	for j in `seq 0 9`
	do
		for k in `seq 0 9`
		do
			is_existen=`find . -name "$i$j$k*"`
			[ -n "$is_existen" ] && {
				echo "$is_existen"
				cd $i$j$k*
				./patch.sh
				cd ..
			}
		done
	done
done
exit 0
