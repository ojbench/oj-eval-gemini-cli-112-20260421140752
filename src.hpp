#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <functional>
// WARNING: NO more headers allowed!

using std::pair;
using std::string;
using std::vector;
using std::map;
using std::function;
namespace final {
    class arguments {
    private:
        // WARNING: You cannot add more member variables.
        int _argc;
        char** _argv;
    public:
        arguments() : _argc(0), _argv(nullptr) {}
        explicit arguments(const string& cmd) : _argc(0), _argv(nullptr) {
            if (cmd.empty()) return;

            vector<string> args;
            string current;
            for (size_t i = 0; i < cmd.length(); ++i) {
                if (cmd[i] == ' ') {
                    if (!current.empty()) {
                        args.push_back(current);
                        current.clear();
                    }
                } else {
                    current += cmd[i];
                }
            }
            if (!current.empty()) {
                args.push_back(current);
            }

            _argc = args.size();
            if (_argc > 0) {
                _argv = new char*[_argc];
                for (int i = 0; i < _argc; ++i) {
                    _argv[i] = new char[args[i].length() + 1];
                    std::strcpy(_argv[i], args[i].c_str());
                }
            }
        }
        ~arguments() {
            if (_argv) {
                for (int i = 0; i < _argc; ++i) {
                    delete[] _argv[i];
                }
                delete[] _argv;
            }
        }

        // Rule of Five
        arguments(const arguments& other) : _argc(other._argc), _argv(nullptr) {
            if (_argc > 0) {
                _argv = new char*[_argc];
                for (int i = 0; i < _argc; ++i) {
                    _argv[i] = new char[std::strlen(other._argv[i]) + 1];
                    std::strcpy(_argv[i], other._argv[i]);
                }
            }
        }

        arguments& operator=(const arguments& other) {
            if (this != &other) {
                if (_argv) {
                    for (int i = 0; i < _argc; ++i) delete[] _argv[i];
                    delete[] _argv;
                }
                _argc = other._argc;
                _argv = nullptr;
                if (_argc > 0) {
                    _argv = new char*[_argc];
                    for (int i = 0; i < _argc; ++i) {
                        _argv[i] = new char[std::strlen(other._argv[i]) + 1];
                        std::strcpy(_argv[i], other._argv[i]);
                    }
                }
            }
            return *this;
        }

        arguments(arguments&& other) noexcept : _argc(other._argc), _argv(other._argv) {
            other._argc = 0;
            other._argv = nullptr;
        }

        arguments& operator=(arguments&& other) noexcept {
            if (this != &other) {
                if (_argv) {
                    for (int i = 0; i < _argc; ++i) delete[] _argv[i];
                    delete[] _argv;
                }
                _argc = other._argc;
                _argv = other._argv;
                other._argc = 0;
                other._argv = nullptr;
            }
            return *this;
        }

        // WARNING: You cannot modify the following functions
        int argc() const { return _argc; }
        char** argv() const { return _argv; }
    };

    // You don't need to modify shell.
    class shell {
    private:
        map<int, arguments> running_list;
    public:
        shell() = default;

        void run(int pid, const string& cmd, const function<void(int, char**)>& invoked) {
            running_list.emplace(pid, cmd);
            invoked(running_list[pid].argc(), running_list[pid].argv());
        }

        int subprocessExit(int pid, int return_value) {
            running_list.erase(pid);
            return return_value;
        }
        vector<int> getRunningList() const {
            vector<int> rt;
            for (auto& pair:running_list)rt.push_back(pair.first);
            return rt;
        }
    };
}
