#include "stdafx.h"

#include "WebSiteParserRestController.h"

#include <set>
#include <sstream> 

using namespace web;
using namespace http;
using namespace WebSiteParser;

WebSiteParserRestController::WebSiteParserRestController(std::unique_ptr<IWebSiteParserCache> cache) 
	: cfx::BasicRestController()
{
	_sentencesCache = std::move(cache);
}

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
		if (path[0] == L"sentences")
		{
			auto response = json::value::object();
			SentencesToJson(response);
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
	auto path = requestPath(message);
	if (!path.empty()) {
		if (path[0] == L"urls") {
			auto urlJson = message.extract_json().get();
			auto urls = urlJson.at(L"urls");
			std::set<utility::string_t> urlList;
			if (urls.is_array())
			{
				auto urlCount = urls.size();
				for (int i=0;i<urlCount; ++i)
				{
					urlList.insert(urls[i].as_string());
				}
			}
			else
			{
				auto urlString = urls.serialize();
				urlList.insert(urlString);
			}
			for (const auto& url : urlList)
				_sentencesCache->AddNewURL(url);
			message.reply(status_codes::Created);
		}
	}
	else {
		message.reply(status_codes::NotFound);
	}
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

void WebSiteParserRestController::SentencesToJson(json::value& response)
{
	const auto& sentences = _sentencesCache->getSentences();
	size_t numberOfSentences = 0;
	std::for_each(sentences.begin(), sentences.end(), [&numberOfSentences](const auto& pair) {numberOfSentences += pair.second.size(); });
	std::wstringstream wss;
	wss << L"0-" << numberOfSentences-1 << "/" << numberOfSentences;
	response[L"Content-Range"] = json::value::string(wss.str());
	json::value urls;
	int urlCounter = 0;
	for (const auto& urlWithSentences : sentences)
	{
		json::value url;
		url[L"url"] = json::value::string(urlWithSentences.first);
		json::value sentences;
		int urlSentenceCounter = 0;
		for (const auto& sentence : urlWithSentences.second)
		{
			sentences[urlSentenceCounter++] = json::value::string(sentence);
		}
		url[L"sentences"] = sentences;
		urls[urlCounter++] = url;
	}
	response[L"urls"] = urls;
}