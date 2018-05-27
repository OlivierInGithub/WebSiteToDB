#include "stdafx.h"

#include "WebSiteParserRestController.h"

using namespace web;
using namespace http;

void WebSiteParserRestController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&WebSiteParserRestController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&WebSiteParserRestController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&WebSiteParserRestController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&WebSiteParserRestController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&WebSiteParserRestController::handlePatch, this, std::placeholders::_1));
}

void WebSiteParserRestController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == L"service" && path[1] == L"test") {
            auto response = json::value::object();
            response[L"version"] = json::value::string(L"0.1.1");
            response[L"status"] = json::value::string(L"ready!");
            message.reply(status_codes::OK, response);
        }
    }
    else {
        message.reply(status_codes::NotFound);
    }
}

void WebSiteParserRestController::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void WebSiteParserRestController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void WebSiteParserRestController::handlePost(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void WebSiteParserRestController::handleDelete(http_request message) {    
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

json::value WebSiteParserRestController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response[L"serviceName"] = json::value::string(L"Web Site Parser Mircroservice");
    response[L"http_method"] = json::value::string(method);
    return response ;
}