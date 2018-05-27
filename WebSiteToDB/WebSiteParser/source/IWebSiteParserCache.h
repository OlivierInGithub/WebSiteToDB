#pragma once

#include <string>
#include <map>
#include <vector>

namespace WebSiteParser {
	typedef std::map<std::wstring, std::vector<std::wstring>> URLSentences;
	class IWebSiteParserCache
	{
	public:
		~IWebSiteParserCache() {}
		virtual void AddNewURL(const std::wstring& newURL) = 0;
		virtual const URLSentences& getSentences() const = 0;
	};
}
