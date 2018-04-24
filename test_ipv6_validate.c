#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <ctype.h>
#include <CUnit/Basic.h>
#include "ipv6_validation.c"
void test_ipv6_validate ()
{
	
	assert_int_equal (Validate_ip6("2003:dead:beef:4dad:23:46:bb:101"), 1);
	assert_int_equal (Validate_ip6("::"), 1);
	assert_int_equal (Validate_ip6("2003:dead:beef:4dad:23:46:192.168.1.2"), 1);
	assert_int_equal (Validate_ip6("2003:dead:beef::46:192.168.1.2"), 1);
	assert_int_equal (Validate_ip6("2003:dead:beef::46:"), 1);
	assert_int_equal (Validate_ip6("2003:dead::beef:4dad:23:192.168.1.2"), 1);
	
	assert_int_equal (Validate_ip6("2003:dead:beef::46::"), 0);
	assert_int_equal (Validate_ip6("2003:dead:beef:4dad:23:46:bb:101:"), 0);
	assert_int_equal (Validate_ip6("2003:dead:beef:4dad:23:46:"), 0);
	assert_int_equal (Validate_ip6("2003:dead:beef:4dad:46:"), 0);
	assert_int_equal (Validate_ip6("2003:::"),0);
	assert_int_equal (Validate_ip6("2003:dead:beef:4dad:23:46:bb:rf"), 0);
	assert_int_equal (Validate_ip6(":df"), 0);
	assert_int_equal (Validate_ip6("2003:dead:beef:4dad:23:46:192.168.1.289"), 0);
	assert_int_equal (Validate_ip6("2003:dead:4dad:23:46:192.168.1.2"), 0);
	assert_int_equal (Validate_ip6("2003:dead::beef:4dad:23:46:192.168.1.2"), 0);
	
	
}

int main()
{
    const UnitTest tests[] = 
    {
        unit_test(test_ipv6_validate),
    };
    return run_tests(tests);
}
