#include <stdio.h>
#include "libExample.h"

CFStringRef c_cfstr(char * str) {
    return CFStringCreateWithCString(NULL, str, kCFStringEncodingMacRoman);
}

id get_nsusernotification() {
    return objc_msgSend((id)objc_getClass("NSUserNotification"),
                            sel_registerName("alloc"),
                            sel_registerName("init"));
}