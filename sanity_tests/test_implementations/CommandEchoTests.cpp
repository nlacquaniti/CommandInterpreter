#include "CommandEchoTests.h"

#include <cassert>
#include <string_view>

namespace CommandEchoTests {
static bool _checkEchoOutput(std::string_view lhsOutput, std::string_view rhsOutput, int lhsIteration, int rhsIteration) {
    assert(lhsOutput == rhsOutput && lhsIteration == rhsIteration);
    return true;
};

ST_TestProcessor::TestFunc countdownParam = [](auto output, auto iteration) {
    return _checkEchoOutput(output, "seconds", iteration, 1); //
};

ST_TestProcessor::TestFunc echoParam = [](auto output, auto iteration) {
    return _checkEchoOutput(output, "command", iteration, 1); //
};

ST_TestProcessor::TestFunc unrecognisedParam = [](auto output, auto iteration) {
    return _checkEchoOutput(output, "command", iteration, 1); //
};
} // namespace CommandEchoTests
