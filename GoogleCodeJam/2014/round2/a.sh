./$1.exe READONLY
cnt=`wc -l $2.poses | awk '{print $1;}'`
echo $cnt
for ((i=1;$i<=$cnt;i++)) ;do
./$1.exe ONETEST $i &
done