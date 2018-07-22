# My Coroutine Experiments
This repo contains the results of some experiments using the Coroutines TS - both by itself, and with libraries like Boost.Asio and Qt, to help me better understand its capabilities.

With the exception of the Qt examples I implemented a really basic coroutine using an integer multiply as an example "asynchronous" task. We wait for it to asynchronously execute and then complete the computation by adding another integer. I figured out the necessary infrastructure (awaitable and promise types) necessary to get this working in each case.

The Qt examples are a bit more complex and involve coroutines that use 0, 1, and 2 asynchronous results delivered via signal. The "normal" Qt implementation is in [qt_basic.cpp](qt_basic.cpp) while the Coroutine version is in [qt_coro.cpp](qt_coro.cpp).

## To Build

It's the usual CMake flow, but your compiler needs to be a recent Clang:

`mkdir build;cd build;cmake -DCMAKE_CXX_COMPILER=/path/to/clang++ ..`

It should be possible to port this to MSVC with only a few changes, if anyone wants to try it.
gcc does not support coroutines at this time.
