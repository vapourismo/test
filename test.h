#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <features.h>

#define COLOR_BLACK 		"\033[0;30m"
#define COLOR_RED 			"\033[0;31m"
#define COLOR_GREEN 		"\033[0;32m"
#define COLOR_YELLOW 		"\033[0;33m"
#define COLOR_BLUE 			"\033[0;34m"
#define COLOR_PINK 			"\033[0;35m"
#define COLOR_CYAN 			"\033[0;36m"
#define COLOR_WHITE 		"\033[0;37m"
#define COLOR_CLEAR 		"\033[0m"

typedef enum {
	TEST_PASSED,
	TEST_FAILED
} __test_status;

typedef struct {
	__test_status status;
	const char* message;
	const char* file;
	int line;
} __test_result;

#define __test_name(name) __test_x_##name
#define __test_passed(name) printf("> " COLOR_BLUE "%s" COLOR_CLEAR " ~ " COLOR_GREEN "%s" COLOR_CLEAR " \n", name, "passed")
#define __test_passed_msg(name, msg) printf("> " COLOR_BLUE "%s" COLOR_CLEAR " ~ " COLOR_GREEN "%s" COLOR_CLEAR ": %s \n", name, "passed", msg)
#define __test_failed(name, reason, file, line) printf("> " COLOR_BLUE "%s" COLOR_CLEAR " ~ " COLOR_RED "%s" COLOR_CLEAR " in " COLOR_BLUE "%s:%i" COLOR_CLEAR ": %s\n", name, "failed", file, line, reason)

/**
 * Indicate the start of a new section
 * Example:
 *     test_section("Main Tests");
 *     test_run(test1)
 *     test_run(test2)
 *     test_run(test3)
 */
#define test_section(section) printf("[ " COLOR_PINK "%s" COLOR_CLEAR " ]\n", section)

/**
 * If expr evaluates to false, mark the current test as failed and print expr.
 * Example:
 *     assert(add(2 + 3) == 5);
 */
#define assert(expr) if(!(expr)){ __test_result tr = {TEST_FAILED, __STRING(expr), __FILE__, __LINE__}; return tr; }

/**
 * If expr evaluates to false, mark the current test as failed and print msg.
 * Example:
 *     assert_msg(2 == 3, "Obviously a user error");
 */
#define assert_msg(expr, msg) if(!(expr)){ __test_result tr = {TEST_FAILED, msg, __FILE__, __LINE__}; return tr; }

/**
 * Mark the current test as finished and exit.
 */
#define test_finish { __test_result tr = {TEST_PASSED, NULL, __FILE__, __LINE__}; return tr; }

/**
 * Mark the current test as finish and exit with a message.
 */
#define test_finish_msg(msg) { __test_result tr = {TEST_PASSED, msg, __FILE__, __LINE__}; return tr; }

/**
 * Mark the current test as failed and exit with a message.
 */
#define test_fail(msg) { __test_result tr = {TEST_FAILED, msg, __FILE__, __LINE__}; return tr; }

/**
 * Run a test.
 * Example:
 *     test_run(my_test);
 */
#define test_run(name) { __test_result tr = __test_name(name)(); if(tr.status == TEST_FAILED){ __test_failed(__STRING(name), tr.message, tr.file, tr.line); }else{ if(tr.message){ __test_passed_msg(__STRING(name), tr.message); }else{ __test_passed(__STRING(name)); } } }

/**
 * Create a new test.
 * Example:
 *     test_new(my_test){
 *         ...
 *         test_finish;
 *     }
 */
#define test_new(name) __test_result __test_name(name)()

#endif
