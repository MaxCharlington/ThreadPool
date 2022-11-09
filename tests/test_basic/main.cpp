#include <threading.hpp>
#include <iostream>
#include <functional>

int main()
{
    using Threads = ThreadPool<std::function<void()>>;

    Threads::TaskQueue tasks;
    for (size_t i = 0; i < 10; i++)
        tasks.push([=]{
            std::cout << i;
        });

    Threads threads{tasks};
    threads.run();
}
