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
        char* msg_buf = (char*) malloc(sizeof(char)*64);
        sprintf(msg_buf, "Illegal Argument: %s", m_msg); 
        return msg_buf;
      }
  };

  class ReferencedUninitialisedValueException: public SimulationException {
    private:
      char* m_msg;
    public:
      ReferencedUninitialisedValueException(char* msg) : m_msg(msg) {}
      const char* what() const throw() { 
        char* msg_buf = (char*) malloc(sizeof(char)*64);
        sprintf(msg_buf, "Referenced uninitialised value: %s", m_msg); 
        return msg_buf;
      }
  };

  // Generator Exceptions
  class GeneratorException: public std::exception { 
    public: 
      virtual const char* what() const throw() { return "Basic Generator Exception.";} 
  };

  class WorldNameFileException: public GeneratorException {
    public:
      const char* what() const throw() { return "Error opening world name file."; }
  };

  class NoMoreUniqueNamesException: public GeneratorException {
    public: 
      const char* what() const throw() { return "No more unique world names."; }
  };

  class NoValidPositionSSException: public GeneratorException {
    public:
      const char* what() const throw() { return "No valid position for new solar system. Consider increasing max size of universe or decreasing amount of worlds generated."; }
  };

  // Universe Exceptions
  class UniverseException: public std::exception { 
    public: 
      virtual const char* what() const throw() { return "Basic Universe Exception.";} 
  };

  class IllegalMaxWorldsException: public UniverseException {
    public:
      const char* what() const throw() { return "Max worlds must be smaller than max unique names"; }
  };

  class IllegalUniverseSizeException: public UniverseException {
    public:
      const char* what() const throw() { return "Size of universe greater than max size."; }
  };

  class ValueExceedsMaximumException: public UniverseException {
    private:
      char* m_msg;
    public:
      ValueExceedsMaximumException(char* msg) : m_msg(msg) {}
      
      const char* what() const throw() { 
        char* msg_buf = (char*) malloc(sizeof(char)*64);
        sprintf(msg_buf, "Value exceeds defined maximum value: %s", m_msg); 
        return msg_buf; 
      }
  };

  class WorldWithoutSystemException: public UniverseException {
    public:
      const char* what() const throw() { return "A world has no solar system"; }  
  };
}


#endif
