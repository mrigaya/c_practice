#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//#define INTADDRSZ 4
int get_delimeter_count(const char * string, char *delimeter) {
	int count = 0;
	while (*string != '\0') {
		if (*string == *delimeter) {
			count +=1;
		}
		string++;
	}
	return count;
}

char to_lower(char ch)
{
  if(ch >= 'A' && ch <= 'Z')
    return (char)('a' + ch - 'A');
  return ch;
}

int Validate_ip4(char *hostname){
	int octets = 0, i,octet_digits = 0;
	char delimeter[] = {"."};
	unsigned char *ip_val;

	unsigned char tmp[4];
	ip_val = tmp;
	*ip_val = 0;

	char *host_tmp = hostname;

	octets = get_delimeter_count(host_tmp, delimeter);
	if (octets != 3){
		printf("Octets are more or less than 3, Invalid IP.\n");
		return 0;
	}

	char *ip_ptr = strchr(host_tmp,'.');
	octet_digits = ip_ptr - host_tmp;
	if (octet_digits >3){
		printf("No. of digits are more than 3 in one octet, Invalid IP.\n");
		return 0;
	}

	while (*host_tmp != '\0'){

		if(!isdigit(*host_tmp)){
			return 0;
		}

		while ( (*host_tmp != *delimeter) && (*host_tmp != '\0')) {
			unsigned int val = (*ip_val) * 10 + (unsigned int)(*host_tmp - '0') ;
			//printf("val is %u and ip_val is %d\n",val, *ip_val);
			*ip_val = val;
			host_tmp++;
			//count += 1;

			if(val >255){
				printf("val %u is greater than 255\n",val);
				return 0;
			}
		}
		
		if((*host_tmp == *delimeter) && (*(host_tmp+1) == '\0'))
			return 0;
		if(*host_tmp != '\0'){
			*ip_val = 0;
			host_tmp++;
		}
	}
	//printf("ip is correct\n");
	return 1;
}
int Validate_ip6(char *hostname){

	int octets = 0, colon_count =0, count = 0, octet_count = 0;
	unsigned char *ip_val, *ip_v4;
	char *host_rem = NULL;
	char delimeter[] = {":"};
	static char ip_digits[] = "0123456789abcdef";

	unsigned char tmp[16];
	ip_val = tmp;
	*ip_val = 0;

	char *host_tmp = hostname;

	if (*host_tmp == ':' && *(host_tmp+1) != ':'){
		return 0;
	}

	octets = get_delimeter_count(host_tmp, delimeter);
	if (octets > 7){
		printf("Octets are more than 7, Invalid IP.\n");
		return 0;
	}

	while (*host_tmp != '\0'){

		while((*host_tmp != ':') &&  (*host_tmp != '\0')){
			if (strchr(ip_digits, to_lower(*host_tmp))){
				host_tmp++;
				count +=1;
				if (count>4)
					return 0;
			}
			else if (*host_tmp == '.')
				break;
			else
				return 0;
		}

		if (*host_tmp == ':') {
			if (*(host_tmp+1) == '\0'){
				return 0;
			}
			if (*(host_tmp+1) == ':') {
				colon_count +=1;
				if(colon_count >1)
					return 0;
			}
			host_tmp++;
			host_rem = host_tmp;
			count = 0;
			octet_count +=1;
			continue;
		}

		if (*host_tmp == '.'){
			if (octet_count > 6)
				return 0;
			printf("host_rem is %s\n", host_rem);
			if(Validate_ip4(host_rem)>0)
				break;
			return 0;
		}
	}
	//printf("ip is correct\n");
	return 1;
}

int main() {
	char hostname[] = "::1234";
	//unsigned char dest_ip[INTADDRSZ] = {'\0'} ;

	if(Validate_ip6(hostname)){
		printf("Wohoo...!!! IP is valid :)\n");
	}
	else {
		//printf("dest_ip is %s\n", dest_ip);
		printf("SAD...!!! IP is not valid :(\n");
	}
	return 0;
}
