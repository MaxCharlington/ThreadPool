#include <thread_pool.hpp>
#include <iostream>

int main()
{
    using TaskQueue = ConcurentQueue<std::function<void()>>;
    using ThreadPool = ThreadPoolImpl<TaskQueue>;

    TaskQueue tasks;
    for (size_t i = 0; i < 10; i++)
        tasks.push([=]{std::cout << i;});
    ThreadPool threads{tasks};
    threads.run(worker<TaskQueue::value_type>);
}
