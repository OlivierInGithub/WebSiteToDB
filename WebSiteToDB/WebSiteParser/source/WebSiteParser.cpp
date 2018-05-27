// WebSiteParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "usr_interrupt_handler.h"

#include "WebSiteParserRestController.h"
#include "WebSiteParserCacheImpl.h"

using namespace cfx;
using namespace WebSiteParser;

int main()
{
	InterruptHandler::hookSIGINT();

	WebSiteParserRestController server(std::make_unique<WebSiteParserCacheImpl>());
	server.setEndpoint(L"http://127.0.0.1:7210/v1/websiteparser/api");

	try {
		// wait for server initialization...
		server.accept().wait();
		std::wcout << "WebSiteParser Microservice now listening for requests at: " << server.endpoint() << '\n';

		InterruptHandler::waitForUserInterrupt();

		server.shutdown().wait();
	}
	catch (std::exception & e) {
		std::cerr << "something wrong happened! :(" << '\n' << e.what();
	}
	catch (...) {
		std::cerr << "something very wrong happened! :(" << '\n';
	}

	return 0;
}

