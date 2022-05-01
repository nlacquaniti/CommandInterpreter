#include "CommandCountdownTests.h"
#include <cassert>
#include <string>

namespace CommandCountdownTests {
static ST_TestProcessor::TestFuncOutput _checkCountdownOutput(std::string_view commandOutput, int currentIteration, int maxIteration) {
    assert(currentIteration <= maxIteration);

    ST_TestProcessor::TestFuncOutput output;

    if (currentIteration < maxIteration) {
        output.HasGeneratedError = commandOutput != (std::to_string(maxIteration - currentIteration) + " seconds remaining");
        output.IsCompleted = false;
        assert(!output.HasGeneratedError);
        return output;
    }

    output.HasGeneratedError = commandOutput != "Countdown complete";
    output.IsCompleted = true;
    assert(!output.HasGeneratedError);
    return output;
}

static ST_TestProcessor::TestFuncOutput _checkInvalidCountdownParam(
    std::string_view commandOutput, std::string_view paramValue, int lhsIteration, int rhsIteration) {
    ST_TestProcessor::TestFuncOutput output;
    const bool bCommandOutputValid = commandOutput != std::string("Invalid countdown period of ") + paramValue.data() + " seconds";
    output.HasGeneratedError = bCommandOutputValid || lhsIteration != rhsIteration;
    output.IsCompleted = true;
    assert(!output.HasGeneratedError);
    return output;
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