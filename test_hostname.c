#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <CUnit/Basic.h>
#include "host_validate.c"
void test_compare_string_with_wildcard ()
{
	
	assert_int_equal (compare_string_with_wildcard("xxxwww.example.com","xxx*.example.com"), 1);
	assert_int_equal (compare_string_with_wildcard("www.example.com","www.example.com"), 1);
	assert_int_equal (compare_string_with_wildcard("www.example.com","*.example.com"), 1);
	assert_int_equal (compare_string_with_wildcard("xxxwww.example.com","xxx*.example.com"), 1);
	assert_int_equal (compare_string_with_wildcard("foo.example.com","f*.example.com"), 1);
	//assert_int_equal (compare_string_with_wildcard("192.168.0.0", "192.168.0.0"), 1);
	
	assert_int_equal (compare_string_with_wildcard("www.example.com","xxx.example.com"), 0);
	assert_int_equal (compare_string_with_wildcard("www.example.com","*"), 0);
	assert_int_equal (compare_string_with_wildcard("www.example.com","*.*.com"), 0);
	assert_int_equal (compare_string_with_wildcard("baa.foo.example.com", "*.example.com"),0);
	assert_int_equal (compare_string_with_wildcard("baa.example.com","f*.example.com"), 0);
	assert_int_equal (compare_string_with_wildcard("example.com","*.com"), 0);
	assert_int_equal (compare_string_with_wildcard("example.com", "*fail.com"),0);
	assert_int_equal (compare_string_with_wildcard("www.example.", "*.example."),0);
	assert_int_equal (compare_string_with_wildcard("www",""), 0);
	assert_int_equal (compare_string_with_wildcard("www","*"), 0);
	
}

int main(void)
{
    const UnitTest tests[] = 
    {
        unit_test(test_compare_string_with_wildcard),
    };
    return run_tests(tests);
}
