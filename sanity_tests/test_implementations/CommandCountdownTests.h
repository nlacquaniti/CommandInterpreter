#ifndef SANITYTESTS_COMMAND_COUNTDOWN_TESTS
#define SANITYTESTS_COMMAND_COUNTDOWN_TESTS

#include "TestProcessor.h"

namespace CommandCountdownTests {
extern ST_TestProcessor::TestFunc minParamValue;
extern ST_TestProcessor::TestFunc oneParamValue;
extern ST_TestProcessor::TestFunc normalParamValue;
extern ST_TestProcessor::TestFunc maxParamValue;
extern ST_TestProcessor::TestFunc minNotValidParamValue;
extern ST_TestProcessor::TestFunc maxNotValidParamValue;
extern ST_TestProcessor::TestFunc notValidNumericParamValue;
} // namespace CommandCountdownTests
#endif // SANITYTESTS_COMMAND_COUNTDOWN_TESTS