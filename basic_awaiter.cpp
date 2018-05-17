// Incorporating an Awaitable

/*
Copyright (c) 2018 Jeff Trull <edaskel@att.net

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <iostream>
#include <experimental/coroutine>

namespace detail
{
// a piece of state accessible to all generators
static int counter = 0;
}

struct my_awaitable {
    struct awaiter {
        bool await_ready() const noexcept { return true; }
        int  await_resume()      noexcept { return detail::counter++; }
        template<typename T>
        void await_suspend(std::experimental::coroutine_handle<T> const&)     noexcept {}
    };
    awaiter operator co_await () { return awaiter{}; }
};

// now we need a coroutine to perform co_await on my awaitable
// co_await must be inside a coroutine, and main cannot be a coroutine, so...

struct await_return_object {
    struct promise_type {
        // coroutine promise requirements:

        auto initial_suspend() const noexcept {
            return std::experimental::suspend_never(); // produce at least one value
        }

        auto final_suspend() const noexcept {
            return std::experimental::suspend_always(); // ?? not sure
        }

        auto return_void() const noexcept {
            return std::experimental::suspend_always(); // ?? not sure
        }

        await_return_object get_return_object() {
            return await_return_object(*this);
        }

        void unhandled_exception() {}  // do nothing :)

    };

    await_return_object(promise_type & p) : m_coro(std::experimental::coroutine_handle<promise_type>::from_promise(p)) {}

private:
    std::experimental::coroutine_handle<promise_type> m_coro;

};

await_return_object try_awaiting() {
    my_awaitable awaitable;
    // count to five
    for (auto i = co_await awaitable; i != 5;i = co_await awaitable) {
        std::cout << "not there yet: " << i << "\n";
    }
    std::cout << "done!\n";
}

int main() {
    auto coro = try_awaiting();
}
