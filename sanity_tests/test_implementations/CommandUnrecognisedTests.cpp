#include "CommandUnrecognisedTests.h"

#include <cassert>
#include <string_view>

namespace CommandUnrecognisedTests {
static bool _checkUnrecognisedCommandOutput(std::string_view lhsOutput, std::string_view rhsOutput, int lhsIteration, int rhsIteration) {
    assert(lhsOutput == rhsOutput && lhsIteration == rhsIteration);
    return true;
}

ST_TestProcessor::TestFunc unknownCommand = [](auto output, auto iteration) {
    return _checkUnrecognisedCommandOutput(output, "Unrecognised command: unknown 0", iteration, 1); //
};

ST_TestProcessor::TestFunc knownCommandWithoutParams = [](auto output, auto iteration) {
    return _checkUnrecognisedCommandOutput(output, "Unrecognised command: countdown", iteration, 1); //
};
} // namespace CommandUnrecognisedTests
