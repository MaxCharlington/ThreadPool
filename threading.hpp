#pragma once

#include <mutex>
#include <vector>

#include "./deps/helpers/concurent_queue.hpp"
#include "thread.hpp"

namespace Threading
{

template <typename T>
class ThreadPool {
    static_assert(requires{ T{}.pop()(); }, "Task queue is required to implement pop method returning callable without parameters");

public:
    using Worker = void(*)(T&);
    using TaskQueue = T;

    ThreadPool(T& task_queue) : m_task_queue{task_queue} {}

    void run(Worker worker = &ThreadPool::worker)
    {
        const auto system_thread_count = std::thread::hardware_concurrency();

        std::vector<Thread> pool;
        pool.reserve(system_thread_count - 2u);

        for (unsigned thread_i = 0; thread_i < system_thread_count; thread_i++)
        {
            pool.emplace_back(worker, m_task_queue, thread_i);
        }
    }

    static void worker(T& task_queue)
    {
        while (true)
        {
            auto task = task_queue.pop();
            if (task) task();
            else break;
        }
    };

private:
    T& m_task_queue;
};

}  //namespace Threading

template<typename Task>
using ThreadPool = Threading::ThreadPool<ConcurrentQueue<Task>>;
