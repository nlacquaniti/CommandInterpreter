#include "CommandCountdownTests.h"
#include <cassert>
#include <string>

namespace CommandCountdownTests {
static bool _checkCountdownOutput(std::string_view commandOutput, int currentIteration, int maxIteration) {
    assert(currentIteration <= maxIteration);

    if (currentIteration < maxIteration) {
        assert(commandOutput == (std::to_string(maxIteration - currentIteration) + " seconds remaining"));
        return false;
    }

    assert(commandOutput == "Countdown complete");
    return true;
}

static bool _checkInvalidCountdownParam(std::string_view commandOutput, std::string_view paramValue, int lhsIteration, int rhsIteration) {
    assert(commandOutput == std::string("Invalid countdown period of ") + paramValue.data() + " seconds");
    assert(lhsIteration == rhsIteration);
    return true;
}

ST_TestProcessor::TestFunc minParamValue = [](auto output, auto iteration) {
    return _checkCountdownOutput(output, iteration, 1); //
};

ST_TestProcessor::TestFunc oneParamValue = [](auto output, auto iteration) {
    return _checkCountdownOutput(output, iteration, 2); //
};

ST_TestProcessor::TestFunc normalParamValue = [](auto output, auto iteration) {
    return _checkCountdownOutput(output, iteration, 6); //
};

ST_TestProcessor::TestFunc maxParamValue = [](auto output, auto iteration) {
    return _checkCountdownOutput(output, iteration, 11); //
};

ST_TestProcessor::TestFunc minNotValidParamValue = [](auto output, auto iteration) {
    return _checkInvalidCountdownParam(output, std::to_string(-1), iteration, 1); //
};

ST_TestProcessor::TestFunc maxNotValidParamValue = [](auto output, auto iteration) {
    return _checkInvalidCountdownParam(output, std::to_string(11), iteration, 1); //
};

ST_TestProcessor::TestFunc notValidNumericParamValue = [](auto output, auto iteration) {
    return _checkInvalidCountdownParam(output, "arg0", iteration, 1); //
};
} // namespace CommandCountdownTests