
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// weirdo double macroing
#define xstr(s) str(s)
#define str(s) #s

#define APP_VERSION_MAJOR     0
#define APP_VERSION_MINOR     0
#define APP_VERSION_REVISION  1
#define APP_VERSION_STR \
  xstr(APP_VERSION_MAJOR) "." \
  xstr(APP_VERSION_MINOR) "." \
  xstr(APP_VERSION_REVISION)

#endif
