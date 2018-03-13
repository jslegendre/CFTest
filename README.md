# CFTest

A working but (probably) unfinished unit testing framework for Core Foundation types and NSObjects in C

#### Why?
For whatever masochistic reason, I enjoy using C and the sense of satisfaction I get from subverting Objective-Cs monopoly over its own runtime (it is written in C after all). Luckily for society though, not many people prefer doing it the hard way which means there aren't a lot of tools for the people who put the C in Objective-C.

I have been working on a C library that allows users to post NSUserNotifications from their C code and I could not find a unit testing framework that worked well for what I was doing.  Having to write all of those `objc_msgSend`s was getting old so I figured I would write my own.

This could also be a great tool for those wanting to learn to interact with macOS through C. Having a test that will tell you when you have finally cracked the case of whatever undocumented task you are trying to accomplish can be a great help.

#### Well that sounds cool but how does it work?
Thanks, it actually is pretty cool and luckily for whichever reader said that I have included an example in the repo.  I will get into some more detail here though.

There are two separate assert functions here: `CF_ASSERT` and `NS_ASSERT`.  As you might have guessed the former is for comparing Core Foundation types (CFStringRef, CFDictionary, etc) and the latter is for comparing any object subclassed from NSObject (NSUserNotification, NSArray, etc). You can also build test suites that alternate between the two.

`CF_ASSERT` compares the two `CFWhatever`s passed to it using the `CFEqual` function and `NS_ASSERT` shoots an `objc_msgSend` with the two NSObjects and the `isEqual:` selector.

##### Okay, that's nice but how do I use it?

###### Building
Using the included `Makefile`, you have a couple of options:

`make`: This will build a static library and a shared library of CFTest plus the example.

`make lib`: This will only build the static and shared library.

`make example`: Should you make the libraries first then decide you want the example, run this.

###### Writing the test
This framework functions like many other unit testing frameworks do actually.  You write a series of `void` functions that contain:

- A setup
- A `(CF/NS)_ASSERT`
- A teardown (you are responsible for free'ing what you use)

In the example, I run a test on a function called `c_cfstr` that takes a C string, converts to and returns a CFStringRef.

The test:

```
void cfstringref_test1() {
	//Initial setup
	char *cstr = "test";
	CFStringRef should_ret = CFSTR("test");

	//Test
	CF_ASSERT(c_cfstr(cstr), should_ret);

	//Teardown
	CFRelease(should_ret);
}
```

The function:
```
CFStringRef c_cfstr(char * str) {
    return CFStringCreateWithCString(NULL, str, kCFStringEncodingMacRoman);
}
```

###### Using the test suites
Suites are a way to group your tests into chunks that can be run separately. In the example I set up a suite of tests to use on `c_cfstr`.  Let's make a suite and give it a name:

```
int main(void) {
	CF_TEST_SUITE * cfstring_suite = CF_new_suite("C string to CFStringRef Suite");
}
```

Now we need to add the test we created earlier to the suite. We do this with `CF_add_test` passing our suite, the name we want to give our test, and a pointer to our test function :

```
int main(void) {
	CF_TEST_SUITE * cfstring_suite = CF_new_suite("C string to CFStringRef Suite");
	CF_add_test(cfstring_suite, "Single word Test",  &cfstringref_test1);
}
```

Once all the tests are added we can run the suite with `RUN_SUITE` and get our results:
```
int main(void) {
	CF_TEST_SUITE * cfstring_suite = CF_new_suite("C string to CFStringRef Suite");
	CF_add_test(cfstring_suite, "Single word Test",  &cfstringref_test1);
	RUN_SUITE(cfstring_suite);
}
```

Output:
```
C string to CFStringRef Suite:
- Single word Test: Passed
- Multi-word Test: Passed
-----------------------------------------------
```

#### That's it?
Pretty much.  This is a simple tool for a niche market. If you have something you would like to add to the project make, a fork and send a PR! I know I am not the worlds best C programmer so any help is appreciated.

And to the three people that use this, have fun.
