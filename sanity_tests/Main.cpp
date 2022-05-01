#include "TestProcessor.h"
#include "test_implementations/CommandCountdownTests.h"
#include "test_implementations/CommandEchoTests.h"
#include "test_implementations/CommandUnrecognisedTests.h"

int main(int, char**) {
    // Echo tests
    ST_TestProcessor::AddTest("echo countdown", CommandEchoTests::countdownParam);
    ST_TestProcessor::AddTest("echo echo", CommandEchoTests::echoParam);
    ST_TestProcessor::AddTest("echo unrecognised", CommandEchoTests::unrecognisedParam);
    //-------------------------------

    // Countdown tests
    ST_TestProcessor::AddTest("countdown 0", CommandCountdownTests::minParamValue);
    ST_TestProcessor::AddTest("countdown 1", CommandCountdownTests::oneParamValue);
    ST_TestProcessor::AddTest("countdown 5", CommandCountdownTests::normalParamValue);
    ST_TestProcessor::AddTest("countdown 10", CommandCountdownTests::maxParamValue);
    ST_TestProcessor::AddTest("countdown -1", CommandCountdownTests::minNotValidParamValue);
    ST_TestProcessor::AddTest("countdown 11", CommandCountdownTests::maxNotValidParamValue);
    ST_TestProcessor::AddTest("countdown arg0", CommandCountdownTests::notValidNumericParamValue);
    // -------------------------------

    // Unrecognised tests
    ST_TestProcessor::AddTest("unknown 0", CommandUnrecognisedTests::unknownCommand);
    ST_TestProcessor::AddTest("countdown", CommandUnrecognisedTests::knownCommandWithoutParams);
    // -------------------------------

    ST_TestProcessor::ProcessTests();
    return 0;
}
