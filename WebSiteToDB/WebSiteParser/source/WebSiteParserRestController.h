#pragma once 

#include "common/BasicRestController.h"

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

class WebSiteParserRestController : public cfx::BasicRestController {
public:
	WebSiteParserRestController() : cfx::BasicRestController() {}
    ~WebSiteParserRestController() {}
    void handleGet(http_request message);
    void handlePut(http_request message);
    void handlePost(http_request message);
    void handlePatch(http_request message);
    void handleDelete(http_request message);
    void initRestOpHandlers() override;    

private:
    static json::value responseNotImpl(const http::method & method);
};