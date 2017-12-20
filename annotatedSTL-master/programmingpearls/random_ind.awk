BEGIN {
    m=ARGV[1];n=ARGV[2]
    for(j=n-m+1;j<=n;j++){
	t = 1+int(j*rand())
	if(t in s) s[j] = 1
	else s[t] = 1
    }
    for (i in s) print i


}
