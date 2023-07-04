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
        OstreamRedirector(std::ostream & stream):
                m_stream{stream}, m_p_cout{nullptr}, m_captured{}
        {
            start();
        }

        ~OstreamRedirector()
        {
            assert(m_p_cout != nullptr);
            if(m_p_cout != nullptr)
            {
                m_stream.rdbuf(m_p_cout);
            }
        }

        void start()
        {
            m_p_cout = m_stream.rdbuf(m_captured.rdbuf());
        }

        void stop()
        {
            assert(m_p_cout != nullptr);
            if(m_p_cout != nullptr)
            {
                m_stream.rdbuf(m_p_cout);
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
        std::ostream & m_stream;
        std::streambuf * m_p_cout;
        std::stringstream m_captured;
    };
}

#endif // OSTREAMREDIRECTOR_HPP
