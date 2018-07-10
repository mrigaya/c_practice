#include<stdio.h>
#include<string.h>
int countDigit(int num){
	int count=0;

	while(num){
		//i =  num % 10;
		num = num/10;
		count++;
	}
	return count;
}

char *numPrintOne(num){
	char a[] = {'\0'};
	switch (num){
		case 0: a[] = "Zero";
			break;
		case 1: a[] = "One";
			break;
		case 2: a[] = "Two";
			break;
		case 3: a[] = "Three";
			break;
		case 4: a[] = "Four";
			break;
		case 5: a[] = "Five";
			break;
		case 6: a[] = "Six";
			break;
		case 7: a[] = "Seven";
			break;
		case 8: a[] = "Eight";
			break;
		case 9: a[] = "Nine";
			break;
		default: printf("Invalid number\n");
			break;
	}
	return a;
}

char *numPrintTwo(num){
	char a[] = {'\0'};
	switch (num){
		case 10: a[] = "Ten";
			break;
		case 11: a[] = "Eleven";
			break;
		case 12: a[] = "Twelve";
			break;
		case 13: a[] = "Thirteen";
			break;
		case 14: a[] = "Fourteen";
			break;
		case 15: a[] = "Fifteen";
			break;
		case 16: a[]  = "Sixteen";
			break;
		case 17: a[] = "Seventeen";
			break;
		case 18: a[] =  "Eighteen";
			break;
		case 19: a[] = "Ninteen";
			break;
		case 20: a[] = "Twenty";
			break;
	}
	return a;
}
char *printNumber(int num){
	int len = countDigit(num);
	char *a;
	if (len == 1){
	a = numPrintOne(num);
	}
	else if(len ==2){
		a= numPrintTwo(num);
	}
	else if(len == 3){
		a[] = "Hundread";
	else if(len == 4){
		a[] = "Thousand";
	}
	else
		printf("Invalid number\n");
	return a;
}

int main(){
	int a = 20;
	//int len = countDigit(a);
	char *str = printNumber(a);
	printf("length is %s\n",str);

	return 0;
}
