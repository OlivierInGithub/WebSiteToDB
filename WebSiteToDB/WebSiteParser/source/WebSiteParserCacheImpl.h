#pragma once
#include <set>
#include "IWebSiteParserCache.h"

namespace WebSiteParser {
	class WebSiteParserCacheImpl :
		public IWebSiteParserCache
	{
	public:
		WebSiteParserCacheImpl() {}
		~WebSiteParserCacheImpl() {}

		virtual void AddNewURL(const std::wstring& newURL) override;
		virtual const URLSentences& getSentences() const override;

	private:
		void ParseSentences(std::wstring url);
		URLSentences _sentences;
		std::set<std::wstring> _urls;
	};
}

