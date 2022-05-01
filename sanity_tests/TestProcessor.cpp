#include "TestProcessor.h"

#include <CommandInterpreter/Control.h>

#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

std::queue<ST_TestProcessor::UserTest> ST_TestProcessor::_tests;

void ST_TestProcessor::AddTest(std::string_view commandToProcess, TestFunc testFunc) {
    _tests.emplace(commandToProcess, std::move(testFunc));
}

void ST_TestProcessor::ClearTest() {
    while (!_tests.empty()) {
        _tests.pop();
    }
}

void ST_TestProcessor::ProcessTests() {
    _print("TEST PROCESSOR START");
    _print("TESTS TO EXECUTE: " + std::to_string(_tests.size()));

    CmdInt_Initialise();
    CmdInt_ProvideCommandExecutedCallback(&_onCommandExecuted);
    _update();
    CmdInt_ShutDown();

    _print("TEST PROCESSOR END");
}

void ST_TestProcessor::_onCommandExecuted(CmdInt_CommandOutput commandOutput, CmdInt_UserContextData userContextData) {
    assert(!_tests.empty());
    auto* test = static_cast<UserTest*>(userContextData);
    test->TestIteration++;

    _print("-------------------------");
    _print("COMMAND ITERATION: " + std::to_string(test->TestIteration) + "\nOUTPUT: " + commandOutput);
    _print("-------------------------");

    test->IsCompleted = test->TestFunc(commandOutput, test->TestIteration);
}

void ST_TestProcessor::_update() {
    using namespace std::chrono;

    _print("##########################################################");
    unsigned int testsCounter = 1;
    while (!_tests.empty()) {
        UserTest& test = _tests.front();

        _print("TEST N" + std::to_string(testsCounter) + " STARTED");
        _print("COMMAND TO PROCESS: " + std::string(test.CommandToProcess));

        CmdInt_ProvideCommand(test.CommandToProcess.data(), &test);

        auto loopStartTime = steady_clock::now();
        while (!test.IsCompleted) {
            duration<double> elapsedTime = steady_clock::now() - loopStartTime;
            if (elapsedTime.count() >= (0.1)) {
                CmdInt_Poll();
                loopStartTime = steady_clock::now();
            }
        }

        _tests.pop();

        _print(("EXECUTION FOR TEST N" + std::to_string(testsCounter) + " ENDED SUCCESSFULLY").c_str());
        ++testsCounter;
        _print("##########################################################");
    }
}

void ST_TestProcessor::_print(std::string_view message) {
    std::cout << message.data() << '\n';
}