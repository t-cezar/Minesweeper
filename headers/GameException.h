#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <exception>
#include <string>

class GameException : public std::exception {
protected:
    std::string msg;
public:
    explicit GameException(std::string message) : msg(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return msg.c_str();
    }
};

class InitCreateException : public GameException {
public:
    explicit InitCreateException(std::string message)
        : GameException("Initialization Error: " + std::move(message)) {}
};

class TextureException : public GameException {
public:
    explicit TextureException(std::string message)
        : GameException("Texture Error: " + std::move(message)) {}
};

class InvalidCoordinateException : public GameException {
public:
    explicit InvalidCoordinateException(std::string message)
        : GameException("Invalid Coordinate: " + std::move(message)) {}
};

class InvalidGridException : public GameException {
public:
    explicit InvalidGridException(std::string message)
        : GameException("Grid Initialization Error: " + std::move(message)) {}
};

#endif
