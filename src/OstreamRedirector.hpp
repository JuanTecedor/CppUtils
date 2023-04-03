#ifndef OSTREAMREDIRECTOR_HPP
#define OSTREAMREDIRECTOR_HPP

#include <iostream>
#include <sstream>
#include <cassert>

namespace juan
{
    class OstreamRedirector
    {
    public:
        OstreamRedirector():
                _pCout{nullptr}, _captured{}
        {
            start();
        }

        ~OstreamRedirector()
        {
            assert(_pCout != nullptr);
            if(_pCout != nullptr)
            {
                std::cout.rdbuf(_pCout);
            }
        }

        void start()
        {
            _pCout = std::cout.rdbuf(_captured.rdbuf());
        }

        void stop()
        {
            assert(_pCout != nullptr);
            if(_pCout != nullptr)
            {
                std::cout.rdbuf(_pCout);
            }
        }

        std::string get()
        {
            return _captured.str();
        }

        void clear()
        {
            _captured.str(std::string());
        }

    private:
        std::streambuf * _pCout;
        std::stringstream _captured;
    };
}

#endif // OSTREAMREDIRECTOR_HPP
