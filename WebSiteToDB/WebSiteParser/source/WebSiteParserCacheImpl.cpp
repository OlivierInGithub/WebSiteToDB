#include "stdafx.h"
#include "WebSiteParserCacheImpl.h"
#include <random>

using namespace WebSiteParser;

void WebSiteParserCacheImpl::AddNewURL(const std::wstring& newURL)
{
	if (_urls.find(newURL) == _urls.end())
	{
		_urls.insert(newURL);
		ParseSentences(newURL);
	}
}

const URLSentences& WebSiteParserCacheImpl::getSentences() const
{
	return _sentences;
}

int GetRandomInt(int min, int max, std::mt19937& rng)
{
	std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max); // distribution in range [min, max]

	return distribution(rng);
}

std::wstring GenerateRandomWord(std::mt19937& rng)
{
	std::wstring word = L"";
	int numberOfLetters = GetRandomInt(1,12, rng);
	for (int i = 0; i < numberOfLetters; ++i)
	{
		char letter = static_cast<char>(GetRandomInt(97,122, rng));
		word += letter;
	}
	return word;
}

void GenerateRandomSentence(std::wstring& sentence, std::mt19937& rng)
{
	sentence = L"";
	int numberOfWords = GetRandomInt(3, 20, rng);
	for (int i = 0; i < numberOfWords; ++i)
	{
		sentence += GenerateRandomWord(rng);
		if (i < numberOfWords - 1)
			sentence += L" ";
	}
	sentence += L".";
}

void WebSiteParserCacheImpl::ParseSentences(std::wstring url)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());

	int numberOfSentences = GetRandomInt(10, 50, rng);
	std::wstring sentence = L"";
	for (int i = 0; i < numberOfSentences; ++i)
	{
		GenerateRandomSentence(sentence, rng);
		_sentences[url].push_back(sentence);
	}
}


