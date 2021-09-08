
#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
	int k,x,y,n,p=0,pvalue,len,i,j=0,strleng=0,inp,count,total,r;
	int xn[1000],yn[1000],dyn[1000],longbinstr[1000],longbinstr1[1000],ptint[100],ctint[1000],ftint[1000],ph1out[1000],ph2out[1000],ph4out[1000],ph5out[1000];
	char pt[1000],ct[700],ft[700];
	printf("Enter plain Text");
	scanf("%99[^\n]",pt);
	printf("enter first layer key");
	scanf("%d",&x);
	printf("enter size of the set in the second layer key");
	scanf("%d",&n);
	printf("enter the set of elements of the second layer key");
	for(i=0;i<n;i++)    scanf("%d",&xn[i]);
	printf("enter y value");
	scanf("%d",&y);
	pvalue=x;
	while(pvalue>=1)
	{
		p++;
		pvalue=pvalue/2;
	}
	len=strlen(pt);
	for(i=0;i<len;i++)    ptint[i]= (int) pt[i];
	for(i=0;i<len;i++)    ph1out[i]= x + ptint[i];
	printf("\n*********ENCRYPTION*********\nFirst phase output is: ");
	for(i=0;i<len;i++)    printf("%d\t",ph1out[i]);
	for(i=0;i<len;i++)    ph2out[i]= xn[i%n] + ph1out[i];
	printf("\nSecond Phase output is: ");
	for(i=0;i<len;i++)    printf("%d\t",ph2out[i]);
	while(y>=1)
	{
		yn[strleng]=y%2;
		strleng++;
		y=y/2;
	}
	for(i=0;i<strleng;i++) dyn[strleng-i-1]=yn[i];
	for(i=0;i<strleng;i++) yn[i]=dyn[i];
	for(i=0;i<len;i++)
	{
		j=j+p-1;
		while(ph2out[i]>=1)
		{
			longbinstr[j]=ph2out[i]%2;
			ph2out[i]=ph2out[i]/2;
			j--;
		}
		j=j+p+1;
	}
	total = 0;
	printf("\nThe long Binary string: ");
	for(i=0;i<j;i++)    printf("%d",longbinstr[i]);
	printf("\n");
	while(total<j)
	{
		for(i=0;i<strleng;i++) 
		{
			longbinstr[total]=longbinstr[total]^yn[i];
			total++;
		}
	}
	r = (len*p)%7;
	for(i=0;i<7-r;i++)
	{
		longbinstr[total]=0;
		total++;
	}
	printf("Third phase output is: ");
	for(i=0;i<len*p+7-r;i++)    printf("%d",longbinstr[i]);
	count=0;
	i=0;
	while(i<total)
	{
		for(j=6;j>=0;j--)
		{
			ctint[count]=ctint[count]+longbinstr[i]*(1<<j);
			i++;
		}
		count++;
	}
	for(i=0;i<(len*p+7-r)/7;i++)    ct[i]= (char) ctint[i];
	printf("\nCipher text is:");
	for(i=0;i<(len*p+7-r)/7;i++)    printf("%c",ct[i]);
	printf("\n\n\n Now taking the cipher text as input and performing decryption\n*********DECRYPTION*********\n");
	int clen=(len*p+7-r)/7;
	for(i=0;i<clen;i++)    ctint[i]= (int) ct[i];
	for(i=0;i<clen;i++)
	{
		for(j=0;j<7;j++)
		{
			longbinstr1[i*7+6-j]=ctint[i]%2;
			ctint[i]=ctint[i]/2;
			if(ctint[i]<=1) { j++; longbinstr1[i*7+6-j]=ctint[i]%2; j++; for(;j<7;j++) longbinstr1[i*7+6-j]=0; }
		}
	}
	total = 0; 
	while(total<clen*7)
	{
		for(i=0;i<strleng;i++) 
		{
			longbinstr1[total]=longbinstr1[total]^yn[i];
			total++;
			if(total>=clen*7) break;
		}
	}
	printf("First phase output is: ");
	for(i=0;i<total;i++)    printf("%d",longbinstr1[i]);
	r = total % p;
	for(i=0;i<r;i++)
	{
		total--;
	}
	count=0;
	i=0;
	while(i<total)
	{
		for(j=p-1;j>=0;j--)
		{
			ph4out[count]=ph4out[count]+longbinstr1[i]*(1<<j);
			i++;
		}
		count++;
	}
	printf("\nSecond phase output is: ");
	for(i=0;i<total/p;i++)    printf("%d\t",ph4out[i]);
	printf("\nThird phase output is: ");
	for(i=0;i<total/p;i++)    ph5out[i]= ph4out[i] - xn[i%n];
	for(i=0;i<total/p;i++)    printf("%d\t",ph5out[i]);
	for(i=0;i<total/p;i++)    ftint[i] = ph5out[i] - x;
	printf("\nThe final plaintext is: ");
	for(i=0;i<total/p;i++)    ft[i]= (char) ftint[i];
	for(i=0;i<total/p;i++)    printf("%c",ft[i]); printf("\n");		
}
