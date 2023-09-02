#include "logMessage.h"

void Handler::receiveMessage(const LogMessage& msg) {
	if (handleMessage(msg)) {
		return;
	}
	else if(!next_){
		throw std::runtime_error("Error: Message should be handled!");
	}
	next_->receiveMessage(msg);
}

bool FatalHandler::handleMessage(const LogMessage& msg) {
	if (msg.type() != LogMessage::Type::fatal_error) return false;
	throw std::runtime_error("Fatal error: " + msg.message());
	return true;
}

bool ErrHandler::handleMessage(const LogMessage& msg) {
	if (msg.type() != LogMessage::Type::error) return false;
	log << "New message received: " << msg.message() << std::endl;
	return true;
}

bool WarnHandler::handleMessage(const LogMessage& msg) {
	if (msg.type() != LogMessage::Type::warning) return false;
	std::cout << "New message received: " << msg.message() << std::endl;
	return true;
}

bool UnknownHandler::handleMessage(const LogMessage& msg) {
	if (msg.type() != LogMessage::Type::unknown_message) return false;
	throw std::runtime_error("New message received: " + msg.message());
	return true;
}