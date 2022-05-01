#include "CommandUnrecognisedTests.h"

#include <cassert>
#include <string_view>

namespace CommandUnrecognisedTests {
static ST_TestProcessor::TestFuncOutput _checkUnrecognisedCommandOutput(
    std::string_view lhsOutput, std::string_view rhsOutput, int lhsIteration, int rhsIteration) {
    ST_TestProcessor::TestFuncOutput output;
    output.HasGeneratedError = lhsOutput != rhsOutput || lhsIteration != rhsIteration;
    output.IsCompleted = true;
    assert(!output.HasGeneratedError);
    return output;
}

ST_TestProcessor::TestFunc unknownCommand = [](auto output, auto iteration) {
    return _checkUnrecognisedCommandOutput(output, "Unrecognised command: unknown 0", iteration, 1); //
};

ST_TestProcessor::TestFunc knownCommandWithoutParams = [](auto output, auto iteration) {
    return _checkUnrecognisedCommandOutput(output, "Unrecognised command: countdown", iteration, 1); //
};
} // namespace CommandUnrecognisedTests
