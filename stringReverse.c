#include<stdio.h>
 int main()
 {	int i, count =0, index =0;
	 char a[] = "My name is XYZ";
	 int len = sizeof(a)/sizeof(a[i]);
	 char b[23] = {'\0'};
	 for(i=len-1; i >= 0; i--)
	 {
		if(a[i] == ' '){
			//printf("Found space\n");
			int j = len - count - i -1;
			int k=1;
			//printf("i is %d\n",i);
			while(j ){
				if(a[i+k] != '\0')
				{

				b[index++] = a[i+k];
			//	printf("i+k is: %d and a[i+k]: %c\n",i+k,a[i+k]);
				j--;
				k++;
				count++;
				if(a[i+k] == ' ')
					break;
				}
				else
					break;
			}
			b[index++] = ' ';
		}
	 }

	 while(a[i+1] != ' '){
		b[index++] = a[i+1];
		i++;
	 }

	 printf("After reversing string: %s\n",b);
	 return 0;
 }
