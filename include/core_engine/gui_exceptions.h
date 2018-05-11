#ifndef GUI_EXCEPTIONS_H
#define GUI_EXCEPTIONS_H

#include <exception>
#include <stdio.h>
#include <stdlib.h>

namespace GUI {
    class GUIException: public std::exception {
        public:
            virtual const char* what() const throw() { return "Basic GUI Exception"; }
  };

    class NoFunctionOnButtonException: public GUIException {
        private:
            char* m_msg;
            int m_id;
        public:
            NoFunctionOnButtonException(int id) : m_id(id) {}
            const char* what() const throw() { 
                char* msg_buf = (char*) malloc(sizeof(char)*64);
                sprintf(msg_buf, "Button pressed with no function assigned - Button ID: %d", m_id); 
                return msg_buf;
            }
  };
}

#endif