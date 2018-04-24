#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char to_lower(char ch)
{
  if(ch >= 'A' && ch <= 'Z')
    return (char)('a' + ch - 'A');
  return ch;
}

int compare_string_no_wildcard(char *pattern, char *hostname) {
	while (*pattern != '\0' && *hostname != '\0') {
		if( to_lower(*pattern) != to_lower(*hostname) ){
			return 0;
		}
		pattern++;
		hostname++;
	}
	if (*pattern == '\0' && *hostname == '\0') {
		return 1;
	}
	return 0;
}

int compare_string_with_wildcard(char *pattern, char *hostname) {
	int cmp_result_first = 0;
	int cmp_result_second = 0;
	int split_count = 0;

	char *pattern_tmp = strdup(pattern);
	char *hostname_tmp = strdup(hostname);

	/* Get string after two dots (.) for comparison (without wildcard)
	/* as to long wildcard is not supported */
	char *p_split_first = strchr(pattern_tmp, '.');
	char *p_split_second = strchr(++p_split_first, '.');

	if (p_split_first != NULL && h_split_first != NULL) {
		p_split_second = strchr(++p_split_first, '.');
		h_split_second = strchr(++h_split_first, '.');
	}
	else {
		return 0;
	}

	if (p_split_second && h_split_second) {
		cmp_result_second = compare_string_no_wildcard(++p_split_second, ++h_split_second);
		if (!cmp_result_second){
			return 0;
		}
	}

	else {
		printf("Should contain atleast two dots (.) in the string \n");
		return 0;
	}

	/* Get string till two dots (.) for wild card comparison */
	int p_index = p_split_second - pattern_tmp;
	int h_index = h_split_second - hostname_tmp;

	*(pattern_tmp + (p_index)) = '\0';
	*(hostname_tmp + (h_index)) = '\0';

	while ((*pattern_tmp != '\0') && (*hostname_tmp != '\0')) {
		/* Continue reading if both the charecters are same */
		if ( to_lower(*pattern_tmp) == to_lower(*hostname_tmp)) {
			pattern_tmp++;
			hostname_tmp++;
		}
		
		/* check if hostname contains wildcard */
		else if (*hostname_tmp == '*') {

			if(*(++hostname_tmp) == '.') {
				/* If hostname contains only * in first octet then skip all charecters in pattern
				/* Then do comparison of next octet*/
				if (split_count == 0) {
 					p_index = p_split_first - pattern_tmp;
 					pattern_tmp += p_index;
 					++hostname_tmp;
 				}
 				else {
 					p_index = p_split_second - pattern_tmp;
 					pattern_tmp += p_index;
 					if (*pattern_tmp == '\0') {
 						return 1;
 					}
				}
			}

			else {
				/* Will support partial wildcard comparison */
				char *h_part = strchr(hostname_tmp, '.');
				h_index = h_part - hostname_tmp;

				/* Skip all charecters in pattern and compare the charecters remained after '*' in hostname string */
				while (*(pattern_tmp + h_index) != '.'){
					pattern_tmp++;
				}

				while (h_index) {

					if ( to_lower(*hostname_tmp) != to_lower(*pattern_tmp) ) {
						return 0;
					}
					pattern_tmp++;
					hostname_tmp++;
					h_index -= 1;
				}
			
			}
			/* After first octet comparison make this on, so that wildcard comparison for next octet will get rejected */
			split_count = 1;
		}
		else if ( to_lower(*pattern_tmp) != to_lower(*hostname_tmp) ) {
				return 0;
		}
	}

	/* Outside while, check whether we have traversed both the strings completely or not */ 
	if ((*pattern_tmp == '\0') && (*hostname_tmp == '\0') ) {
			return 1;
	}
	else {
		return 0;
	}
}

int main() {
	char pattern[128] = "xxxwww.EXAMPle.test.com";
	char hostname[128] = "*.*l.test.com";

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
