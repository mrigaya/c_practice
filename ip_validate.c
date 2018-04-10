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

int Validate_ip(const char *hostname){
	int octets = 0, i,octet_digits = 0;
	char delimeter[] = {"."};
	unsigned char *ip_val;

	unsigned char tmp[INTADDRSZ];
	ip_val = tmp;
	*ip_val = 0;

	const char *host_tmp = hostname;

	octets = get_delimeter_count(host_tmp, delimeter);
	if (octets != 3){
		printf("Octets are more or less than 3, Invalid IP.\n");
		return 0;
	}

	const char *ip_ptr = strchr(host_tmp,'.');
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
		
		if(*host_tmp != '\0'){
			*ip_val = 0;
			host_tmp++;
			//count = 0;
		}
	}
	//printf("ip is correct\n");
	return 1;
}

int main() {
	char hostname[] = "192.168.1.2";
	//unsigned char dest_ip[INTADDRSZ] = {'\0'} ;

	if(Validate_ip(hostname)){
		printf("Wohoo...!!! IP is valid :)\n");
	}
	else {
		//printf("dest_ip is %s\n", dest_ip);
		printf("SAD...!!! IP is not valid :(\n");
	}
	return 0;
}