#pragma once

#include <iostream>
#include <memory>
#include <fstream>

class LogMessage {
public:
    enum class Type {
        warning,
        error,
        fatal_error,
        unknown_message
    };

    ~LogMessage() = default;
    virtual Type type() const = 0;
    virtual const std::string message() const = 0;
};

class FatalMessage : public LogMessage{
public:
    Type type() const override { return Type::fatal_error; };
    const std::string message() const override { return "Some very fatal error"; };
};

class ErrMessage : public LogMessage {
public:
    Type type() const override { return Type::error; };
    const std::string message() const override { return "Some not quite fatal error"; };
};

class WarnMessage : public LogMessage {
public:
    Type type() const override { return Type::warning; };
    const std::string message() const override { return "The last Chinese warning"; };
};

class UnknownMessage : public LogMessage {
public:
    Type type() const override { return Type::unknown_message; };
    const std::string message() const override { return "Scary, very scary! We don't know what it is, if we knew what it is, we don't know what it is"; };
};

class Handler {
public:
    explicit Handler(std::unique_ptr<Handler> next) : next_(std::move(next)) {}
    virtual ~Handler() = default;

    void receiveMessage(const LogMessage& msg);
private:
    virtual bool handleMessage(const LogMessage& msg) = 0;
    std::unique_ptr<Handler> next_;
};

class FatalHandler : public Handler {
public:
    using Handler::Handler;
private:
    bool handleMessage(const LogMessage& msg) override;
};

class ErrHandler : public Handler {
public:
    using Handler::Handler;
    ~ErrHandler() { log.close(); }
private:
    bool handleMessage(const LogMessage& msg) override;
    std::ofstream log{ "logs.txt" };
};

class WarnHandler : public Handler {
public:
    using Handler::Handler;
private:
    bool handleMessage(const LogMessage& msg) override;
};

class UnknownHandler : public Handler {
public:
    using Handler::Handler;
private:
    bool handleMessage(const LogMessage& msg) override;
};