#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>
#include "CFTest.h"

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define RESET "\x1B[0m"

_Bool g_test_passed;

void CF_ASSERT(CFTypeRef test, CFTypeRef should){
	Boolean equal = CFEqual(test, should);
	if (!equal) {
	    g_test_passed = false;
	} else {
		g_test_passed = true;
	}
}

void NS_ASSERT(id test, id should) {
	Boolean equal = (Boolean)objc_msgSend(test, sel_registerName("isEqual:"), should);
	if(!equal) {
		g_test_passed = false;
	} else {
		g_test_passed = true;
	}
}

void CF_add_test(CF_TEST_SUITE *test_suite, char *name, void (*test)()){
	test();
	CF_TEST *new_test = malloc(sizeof(CF_TEST));
	new_test->name = name;
	new_test->pass = g_test_passed;

	test_suite->all_tests = realloc(test_suite->all_tests, sizeof(CF_TEST) * (test_suite->test_count + 1));
	test_suite->all_tests[test_suite->test_count] = (CF_TEST *)malloc(sizeof(CF_TEST));
	test_suite->all_tests[test_suite->test_count] = new_test;

	test_suite->test_count++;
}

CF_TEST_SUITE * CF_new_suite(char *name) {
	CF_TEST_SUITE *test_suite = malloc(sizeof(CF_TEST_SUITE));
	test_suite->name = name;
	test_suite->test_count = 0;
	test_suite->all_tests = malloc(sizeof(CF_TEST));
	return test_suite;	
}

void print_results(CF_TEST **all_tests, uintptr_t test_count) {
	uintptr_t i;
	for(i = 0; i < test_count; i++) {
		printf("- %s: ", all_tests[i]->name);
		if(all_tests[i]->pass) {
			printf(KGRN "Passed\n" RESET);
		} else {
			printf(KRED "Failed\n" RESET);
			break;
		}
	}
	printf("-----------------------------------------------\n");
}

void RUN_SUITE(CF_TEST_SUITE *test_suite) {
	printf(KYEL "%s:\n" RESET, test_suite->name);
	print_results(test_suite->all_tests, test_suite->test_count);
	free(test_suite);
}