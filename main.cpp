#include <iostream>

#include "logMessage.h"

int main() {
	auto fatal_handler = std::make_unique<FatalHandler>(nullptr);
	auto error_handler = std::make_unique<ErrHandler>(std::move(fatal_handler));
	auto warning_handler = std::make_unique<WarnHandler>(std::move(error_handler));
	auto unkown_msg_handler = std::make_unique<UnknownHandler>(std::move(warning_handler));

	try 
	{
		unkown_msg_handler->receiveMessage(FatalMessage());
		unkown_msg_handler->receiveMessage(WarnMessage());
		unkown_msg_handler->receiveMessage(ErrMessage());
		unkown_msg_handler->receiveMessage(UnknownMessage());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}