#! /bin/bash


function cp_dirAfile_to_dirB()
{
 local dirB=$2
 local dirA=$1
 
 if test ! -d ${dirB}
 then
 	mkdir ${dirB}
 fi
 
 for file in ${dirA}/*
 do
 	if test -d ${file}
 	then
 		tmpB=${dirB}/${file#${dirA}/}
 		if test -d ${tmpB}
 		then
 			cp_dirAfile_to_dirB ${file} ${tmpB}
		else
			mkdir ${tmpB}
			cp_dirAfile_to_dirB ${file} ${tmpB}
 		fi
 	elif test -f ${file}
 	then
 		tmpB=${dirB}/${file#${dirA}/}
 		if test -f ${tmpB}
 		then
 			stampA=`stat ${file} | grep -i Modify | awk -F. '{print $1}' | awk '{print $2$3}'| awk -F- '{print $1$2$3}' | awk -F: '{print $1$2$3}'`
 			stampB=`stat ${tmpB} | grep -i Modify | awk -F. '{print $1}' | awk '{print $2$3}'| awk -F- '{print $1$2$3}' | awk -F: '{print $1$2$3}'`
 			if [ ${stampA} -gt ${stampB} ]
 			then
 				cp -f ${file} ${tmpB}
 			else
 				cp -f ${tmpB} ${file}
 			fi
		else 
			cp -f ${file} ${tmpB}
 		fi
 	fi
 done
}

if test -d $2 && test -d $1
then
	cp_dirAfile_to_dirB $1 $2
else
	echo "format:sync_src.sh dirArc dirDst"
fi


	


