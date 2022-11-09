#include <thread_pool.hpp>
#include <iostream>
#include <functional>

int main()
{
    using TaskQueue = ConcurrentQueue<std::function<void()>>;
    using Threads = ThreadPool<TaskQueue>;

    TaskQueue tasks;
    for (size_t i = 0; i < 10; i++)
        tasks.push([=]{
            std::cout << i;
        });

    Threads threads{tasks};
    threads.run();
}
