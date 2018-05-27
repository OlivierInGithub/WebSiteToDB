#pragma once 

#include <memory>

#include "common/BasicRestController.h"
#include "IWebSiteParserCache.h"

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

namespace WebSiteParser {
	class WebSiteParserRestController : public cfx::BasicRestController {
	public:
		WebSiteParserRestController(std::unique_ptr<IWebSiteParserCache> cache);
		~WebSiteParserRestController() {}
		void handleGet(http_request message);
		void handlePut(http_request message);
		void handlePost(http_request message);
		void handlePatch(http_request message);
		void handleDelete(http_request message);
		void initRestOpHandlers() override;

	private:
		static json::value responseNotImpl(const http::method & method);

		void SentencesToJson(json::value& sentences);

		std::unique_ptr<IWebSiteParserCache> _sentencesCache;
	};
}