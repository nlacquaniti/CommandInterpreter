#include <CommandInterpreter/Control.h>
#include <CommandInterpreter/Interpreter.h>
#include <chrono>
#include <iostream>

static void _commandExecutedCallback(CmdInt_CommandOutput commandOutput, CmdInt_UserContextData userContextData) {
    const auto* data = static_cast<std::string_view*>(userContextData);
    std::cout <<  *data << " command" <<" output: " << commandOutput << '\n';
}

int main(int, char**) {
    using namespace std::chrono;

    const auto appStartTime = steady_clock::now();

    // This executable links against your library.
    // You may perform any sanity tests here that you wish,
    // to verify that your code works as expected.
    // Please leave these tests in your final solution,
    // as they will add to your overall evaluation.
    CmdInt_Initialise();

    CmdInt_ProvideCommandExecutedCallback(&_commandExecutedCallback);

    std::string_view echoData("echo");
    CmdInt_ProvideCommand("echo countdown", &echoData);

    std::string_view countdownData("countdown 1");
    CmdInt_ProvideCommand("countdown 3", &countdownData);

    std::string_view countdownData2("countdown 2");
    CmdInt_ProvideCommand("countdown 3", &countdownData2);

    const auto loopStartTime = steady_clock::now();
    duration<double> loopElapsedTime(0);
    while (loopElapsedTime.count() < 10) {
        loopElapsedTime = steady_clock::now() - loopStartTime;
        CmdInt_Poll();
    }

    CmdInt_ShutDown();

    const duration<double> appElapsedTime = steady_clock::now() - appStartTime;
    std::cout << "test took: " << appElapsedTime.count() << "s\n";

    return 0;
}
