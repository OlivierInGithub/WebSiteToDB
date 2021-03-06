//
//  Created by Ivan Mejia on 12/03/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#pragma once

#include <string>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;
using namespace http::experimental::listener;

namespace cfx {
    class BasicRestController {
    protected:
        http_listener _listener; // main micro service network endpoint

    public:
		BasicRestController() {}
		virtual ~BasicRestController() {}

		void setEndpoint(const utility::string_t & value) {
			_listener = http_listener(value);
		}
        utility::string_t endpoint() const {
			return _listener.uri().to_string();
		}
		pplx::task<void> accept() {
			initRestOpHandlers();
			return _listener.open();
		}
		pplx::task<void> shutdown() {
			return _listener.close();
		}

		virtual void initRestOpHandlers() = 0;

		std::vector<utility::string_t> requestPath(const http_request & message) {
			auto relativePath = uri::decode(message.relative_uri().path());
			return uri::split_path(relativePath);
		}
    };
}