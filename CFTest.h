#ifndef CFTEST_H
#define CFTEST_H

typedef struct cftest {
	char *name;
	_Bool pass;
}CF_TEST;

typedef struct cftestsuite {
	char *name;
	uintptr_t test_count;
	CF_TEST **all_tests;
}CF_TEST_SUITE;

_Bool g_test_passed;

void CF_add_test(CF_TEST_SUITE *test_suite, char *name, void (*test)());
void CF_ASSERT(CFTypeRef test, CFTypeRef should);
void NS_ASSERT(id test, id should);
CF_TEST_SUITE * CF_new_suite(char *name);
void RUN_SUITE(CF_TEST_SUITE *test_suite);
#endif