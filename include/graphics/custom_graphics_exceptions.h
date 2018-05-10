#ifndef CUSTOM_GRAPHICS_EXCEPTIONS_H
#define CUSTOM_GRAPHICS_EXCEPTIONS_H

#include <exception>
#include <stdio.h>
#include <stdlib.h>

class InitializationException: public std::exception {
    private:
      char* m_msg;
    public:
        InitializationException(char* msg) : m_msg(msg) {}
        virtual const char* what() const throw() { 
            char* msg_buf = (char*) malloc(sizeof(char)*64);
            sprintf(msg_buf, "Error while initializing: %s", m_msg); 
            return msg_buf;
        }
};

#endif