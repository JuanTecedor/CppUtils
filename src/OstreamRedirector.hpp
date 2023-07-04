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
                m_p_cout{nullptr}, m_captured{}
        {
            start();
        }

        ~OstreamRedirector()
        {
            assert(m_p_cout != nullptr);
            if(m_p_cout != nullptr)
            {
                std::cout.rdbuf(m_p_cout);
            }
        }

        void start()
        {
            m_p_cout = std::cout.rdbuf(m_captured.rdbuf());
        }

        void stop()
        {
            assert(m_p_cout != nullptr);
            if(m_p_cout != nullptr)
            {
                std::cout.rdbuf(m_p_cout);
            }
        }

        std::string get()
        {
            return m_captured.str();
        }

        void clear()
        {
            m_captured.str(std::string());
        }

    private:
        std::streambuf * m_p_cout;
        std::stringstream m_captured;
    };
}

#endif // OSTREAMREDIRECTOR_HPP
