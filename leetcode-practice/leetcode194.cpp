
NF                 浏览记录的域的个数
NR                 已读的记录数


awk '
{
	for(i=1; i<=NF; i++)
	{
		if(NR == 1) 
			s[i] = $i;
		else
			s[i] = s[i] " " $i;
	}
}
END {
	for(i=1; s[i]!=""; i++)
	{
		print s[i]
	}
}
' file.txt