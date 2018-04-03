#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_string_no_wildcard(char *pattern1, char *pattern2) {
	while (*pattern1 != '\0' && *pattern2 != '\0') {
		if( *pattern1 != *pattern2){
			return 0;
		}
		pattern1++;
		pattern2++;
	}
	return 1;
}

int compare_string_with_wildcard(char *pattern1, char *pattern2) {
	int cmp_result_first = 0;
	int cmp_result_second = 0;
	static int split_count = 0;

	char *pattern1_tmp = strdup(pattern1);
	char *pattern2_tmp = strdup(pattern2);

	char *p1_split_first = strchr(pattern1_tmp,'.');
	char *p1_split_second = strchr(++p1_split_first, '.');

	char *p2_split_first = strchr(pattern2_tmp,'.');
	char *p2_split_second = strchr(++p2_split_first, '.');

	if (p1_split_second && p2_split_second) {
		cmp_result_second = compare_string_no_wildcard(++p1_split_second, ++p2_split_second);
		printf("cmp_result_second %d\n", cmp_result_second);
	}

	else {
		printf("Should contain atleast two dots (.) in the string \n");
		return 0;
	}

	int p1_index = p1_split_second - pattern1_tmp;
	int p2_index = p2_split_second - pattern2_tmp;

	*(pattern1_tmp + (p1_index)) = '\0';
	*(pattern2_tmp + (p2_index)) = '\0';

	printf("p1_index is %d and p2_index is %d\n", p1_index,p2_index);

	printf("p1_split_second is %s and p2_split_second is %s\n",p1_split_first, p2_split_second );



	printf("pattern1 is %s and pattern1_tmp is %s\n",pattern1, pattern1_tmp);
	printf("pattern2 is %s and pattern2_tmp is %s\n",pattern2, pattern2_tmp);

	while ((*pattern1_tmp != '\0') && (*pattern2_tmp != '\0')) {
		if (*pattern1_tmp == *pattern2_tmp) {
			++pattern1_tmp;
			++pattern2_tmp;
			continue;
		}
		else if (*pattern1_tmp == '*') {
			if(*(++pattern1_tmp) == '.') {
				//++pattern1_tmp;
				if (split_count == 0) {
					p2_index = p2_split_first - pattern2_tmp;
					pattern2_tmp += p2_index;
					
				}
				else {
					p2_index = p2_split_second - pattern2_tmp;
					pattern2_tmp += p2_index;
					if (*pattern2_tmp == '\0') {
						return 1 && cmp_result_second;
					}
				}
				
				continue;
				printf ("pattern2_tmp is %s\n",pattern2_tmp);
			}

			else {
				
				char *p1_part = strchr(pattern1_tmp, '.');
				p1_index = p1_part - pattern1_tmp;
				//char p1_cmp_string[p1_index] = {'\0'};
				while (*(pattern2_tmp+p1_index) != '.'){
					pattern2_tmp++;
				}
				//printf("Before while:p1_index is %d\n",p1_index);
				//printf ("Before while:pattern1_tmp is %s\n",pattern1_tmp);
				while (p1_index) {

					if ((*pattern1_tmp != *pattern2_tmp )) {
						return 0;
					}

					else {
						//printf ("pattern1_tmp is ... %s\n",pattern1_tmp);
						//printf ("pattern2_tmp is ... %s\n",pattern2_tmp);
						pattern1_tmp++;
						pattern2_tmp++;
						p1_index -= 1;
					}
				}

			}
			split_count += 1;

		}

		else if (*pattern2_tmp == '*') {
			printf("split_count  is %d\n",split_count );
			if(*(++pattern2_tmp) == '.') {
				
				if (split_count == 0) {
					p1_index = p1_split_first - pattern1_tmp;
					pattern1_tmp += p1_index;
					
					++pattern2_tmp;
					
				}
				else {
					p1_index = p1_split_second - pattern1_tmp;
					pattern1_tmp += p1_index;
					printf("String:pattern1_tmp is %s\n", pattern1_tmp);
					if (*pattern1_tmp == '\0') {
						return 1 && cmp_result_second;
					}
				}
				
				printf ("pattern2_tmp is %s\n",pattern2_tmp);
				continue;
				
			}

			else {
				
				char *p2_part = strchr(pattern2_tmp, '.');
				p2_index = p2_part - pattern2_tmp;
				//char p1_cmp_string[p1_index] = {'\0'};
				while (*(pattern1_tmp+p2_index) != '.'){
					pattern1_tmp++;
				}
				printf("Before while:p2_index is %d\n",p2_index);
				printf ("Before while:pattern2_tmp is %s\n",pattern2_tmp);
				while (p2_index) {

					if ((*pattern2_tmp != *pattern1_tmp )) {
						return 0;
					}

					else {
						printf ("pattern1_tmp is ... %s\n",pattern1_tmp);
						printf ("pattern2_tmp is ... %s\n",pattern2_tmp);
						pattern1_tmp++;
						pattern2_tmp++;
						p2_index -= 1;
					}
				}

				printf ("After while:pattern2_tmp is %s\n",pattern2_tmp);
				printf ("After while:pattern1_tmp is %s\n",pattern1_tmp);

				
			}
			split_count += 1;
			//pattern1_tmp++;
			//pattern2_tmp++;
			//continue;
		}

		else if (*pattern1_tmp != *pattern2_tmp) {
				return 0;
		}
	}

printf ("pattern1_tmp is ... %s\n",pattern1_tmp);
printf ("pattern2_tmp is ... %s\n",pattern2_tmp);
	if ((*pattern1_tmp == '\0') && (*pattern2_tmp == '\0') ) {
		if(cmp_result_second){
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

int main() {
	char pattern[128] = "smaa.*st.test.com";
	char hostname[128] = "*smaa.*.test.com";
	char delimeter[2] = ".";


	if(compare_string_with_wildcard(pattern,hostname)){
		printf("String Matched\n");
		printf("String comparison is SUCCESS.\n");
	}
	else {
		printf("Both the Strings are not Same\n");
		printf("String comparison is FAILED.\n");
	}
	return 0;
}