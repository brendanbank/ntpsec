extern "C" {
#include "unity.h"
#include "unity_fixture.h"
}

TEST_GROUP(vi64ops);

TEST_SETUP(vi64ops) {}

TEST_TEAR_DOWN(vi64ops) {}

#include "libntptest.h"

extern "C" {
#include "vint64ops.h"
}

class vi64Test : public libntptest {
public:
	bool IsEqual(const vint64 &expected, const vint64 &actual) {
		if (0 == memcmp(&expected, &actual, sizeof(vint64))) {
			return true;
		} else {
			return false
			    << "expected: "
			    << std::hex << expected.D_s.hi << '.'
			    << std::hex << expected.D_s.lo
			    << " but was "
			    << std::hex << actual.D_s.hi << '.'
			    << std::hex << actual.D_s.lo;
		}
	}
};

// ----------------------------------------------------------------------
// test number parser
TEST(vi64, ParseVUI64_pos) {
	vint64 act, exp;
	const char *sp;
	char       *ep;

	sp         = "1234x";
	exp.D_s.hi = 0;
	exp.D_s.lo = 1234;
	act        = strtouv64(sp, &ep, 0);
	TEST_ASSERT_TRUE(IsEqual(exp, act));
	TEST_ASSERT_EQUAL(*ep, 'x');
}

TEST(vi64, ParseVUI64_neg) {
	vint64 act, exp;
	const char *sp;
	char       *ep;

	sp         = "-1234x";
	exp.D_s.hi = ~0;
	exp.D_s.lo = -1234;
	act        = strtouv64(sp, &ep, 0);
	TEST_ASSERT_TRUE(IsEqual(exp, act));
	TEST_ASSERT_EQUAL(*ep, 'x');
}

TEST(vi64, ParseVUI64_case) {
	vint64 act, exp;
	const char *sp;
	char       *ep;

	sp         = "0123456789AbCdEf";
	exp.D_s.hi = 0x01234567;
	exp.D_s.lo = 0x89ABCDEF;
	act        = strtouv64(sp, &ep, 16);
	TEST_ASSERT_TRUE(IsEqual(exp, act));
	TEST_ASSERT_EQUAL(*ep, '\0');
}


TEST_GROUP_RUNNER(vi64) {
	RUN_TEST_CASE(vi64, ParseVUI64_pos);
	RUN_TEST_CASE(vi64, ParseVUI64_neg);
	RUN_TEST_CASE(vi64, ParseVUI64_case);
}
