#include<stdio.h>

int main(){
	int i,n,temp;
	char a[] = "abc3,4fsaa*dg4wxyzac56z";
	printf("Enter the number for encryption: \t");
	scanf("%d",&n);
	printf("String before encryption: %s\n",a);
	int len = sizeof(a)/sizeof(a[0]);
	for (i=0; i<len; i++)
	{
		if (((a[i] >= 'A') || (a[i] >= 'a')) && ((a[i] <= ('Z' - n)) || (a[i] <= ('z' - n)))){
			a[i] = a[i] + n;
		}
		else if(a[i]+n >'Z' || a[i]+n > 'z'){	
			if(a[i]+n >'Z'){
				temp = 'Z' - a[i];
				temp = n - temp -1;
				a[i] = 'A' + temp;
			}
			else{
				temp = 'z' - a[i];
				temp = n-temp -1;
				a[i] = 'a' +temp;
			}
		}
	}
	printf("String after encryption: %s\n",a);
	return 0;
}
