#include "CommandEchoTests.h"

#include <cassert>
#include <string_view>

namespace CommandEchoTests {
static ST_TestProcessor::TestFuncOutput _checkEchoOutput(std::string_view lhsOutput, std::string_view rhsOutput, int lhsIteration, int rhsIteration) {
    ST_TestProcessor::TestFuncOutput output;
    output.HasGeneratedError = lhsOutput != rhsOutput || lhsIteration != rhsIteration;
    output.IsCompleted = true;
    assert(!output.HasGeneratedError);
    return output;
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
