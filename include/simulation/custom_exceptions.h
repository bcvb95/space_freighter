#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
#include <stdio.h>
#include <stdlib.h>

// Simulation Exceptions
namespace Simulation {
  // Main Simulation Exceptions
  class SimulationException: public std::exception {
    public:
      virtual const char* what() const throw() { return "Basic Simulation Exception"; }
  };

  class IllegalArgumentException: public SimulationException {
    private:
      char* m_msg;
    public:
      IllegalArgumentException(char* msg) : m_msg(msg) {}
      const char* what() const throw() { 
        char* msg_buf = (char*) malloc(sizeof(char)*50);
        sprintf(msg_buf, "Illegal Argument: %s", m_msg); 
        return msg_buf;
      }
  };

  // Universe Exceptions
  class UniverseException: public std::exception { 
    public: 
      virtual const char* what() const throw() { return "Basic Universe Exception.";} 
  };

  class WorldNameFileException: public UniverseException {
    public:
      const char* what() const throw() { return "Error opening world name file."; }
  };

  class NoMoreUniqueNamesException: public UniverseException {
    public: 
      const char* what() const throw() { return "No more unique world names."; }
  };

  class IllegalMaxWorldsException: public UniverseException {
    public:
      const char* what() const throw() { return "Max worlds must be smaller than max unique names"; }
  };

  class IllegalUniverseSizeException: public UniverseException {
    public:
      const char* what() const throw() { return "Size of universe greater than max size."; }
  };
}


#endif
