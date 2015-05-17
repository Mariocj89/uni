lista=`ls -r $1`
for i in $lista
do
	if [ -d $1/$i ]
	then
		sh $0 $1/$i
		echo $1/$i
	fi
done
