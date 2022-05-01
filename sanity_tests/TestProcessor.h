#ifndef ST_TEST_PROCESSOR_H
#define ST_TEST_PROCESSOR_H

#include <CommandInterpreter/Interpreter.h>

#include <functional>
#include <queue>
#include <string_view>

class ST_TestProcessor {
public:
    struct TestFuncOutput {
        bool IsCompleted = false;
        bool HasGeneratedError = false;
    };

    using TestFunc = std::function<TestFuncOutput(std::string_view, int)>;

    static void AddTest(std::string_view commandToProcess, TestFunc testFunc);
    static void ClearTest();
    static void ProcessTests();

private:
    struct UserTest {
        UserTest(std::string_view commandToProcess, TestFunc testFunc)
            : CommandToProcess(commandToProcess)
            , UserTestFunc(std::move(testFunc))
            , TestIteration(0) {}

        std::string_view CommandToProcess;
        TestFunc UserTestFunc;
        int TestIteration;
        TestFuncOutput Output;
    };

    static void _onCommandExecuted(CmdInt_CommandOutput commandOutput, CmdInt_UserContextData userContextData);
    static void _update();
    static void _print(std::string_view message);

    static std::queue<UserTest> _tests;
};
#endif // ST_TEST_PROCESSOR_H