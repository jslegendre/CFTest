#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>

#include "CFTest.h"
#include "libExample.h"

void cfstringref_test1() {
	//Initial setup
	char *cstr = "test";
	CFStringRef should_ret = CFSTR("test");

	//Should pass
	CF_ASSERT(c_cfstr(cstr), should_ret);

	//Teardown
	CFRelease(should_ret);
}

void cfstringref_test2(){
	char *cstr = "this is a test";
	CFStringRef should_ret = CFSTR("this is a test");
	CF_ASSERT(c_cfstr(cstr), should_ret);
	CFRelease(should_ret);
}

void nsusernotification_test() {
	 id notif = objc_msgSend((id)objc_getClass("NSUserNotification"),
                            sel_registerName("alloc"),
                            sel_registerName("init"));

	 NS_ASSERT(get_nsusernotification(), notif);

	 objc_msgSend(notif, sel_registerName("release"));
}

int main(void) {
	CF_TEST_SUITE * cfstring_suite = CF_new_suite("C string to CFStringRef Suite");
	CF_add_test(cfstring_suite, "Single word Test",  &cfstringref_test1);
	CF_add_test(cfstring_suite, "Multi-word Test",  &cfstringref_test2);
	RUN_SUITE(cfstring_suite);

	CF_TEST_SUITE * nsnotif_suite = CF_new_suite("NSUserNotification Suite");
	CF_add_test(nsnotif_suite, "NSUserNotification does create",  &nsusernotification_test);
	RUN_SUITE(nsnotif_suite);
}