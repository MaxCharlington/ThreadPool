#pragma once

#include <mutex>
#include <vector>

#include "./deps/helpers/concurent_queue.hpp"
#include "thread.hpp"

namespace Threading
{

// template<typename TaskQ>
// concept TaskQueueC = requires(TaskQ q){
//     { q.pop() } -> std::convertible_to<bool>;
//     { q.pop().value()() };
// };

template <typename T, std::size_t ThreadCount = 0>
class ThreadPool {
public:
    using Worker = void(*)(T&);
    using TaskQueue = T;

    ThreadPool(T& task_queue) : m_task_queue{task_queue} {}

    void run(Worker worker = &ThreadPool::worker)
    {
        const auto thread_cnt = (ThreadCount == 0) ? (std::thread::hardware_concurrency() - 2u) : ThreadCount;

        std::vector<Thread> pool;
        pool.reserve(thread_cnt);

        for (unsigned thread_i = 0; thread_i < thread_cnt; thread_i++)
        {
            pool.emplace_back(worker, m_task_queue, thread_i);
        }
    }

    static void worker(T& task_queue)
    {
        while (true)
        {
            auto task = task_queue.pop();
            if (task) task.value()();
            else break;
        }
    };

private:
    T& m_task_queue;
};

}  //namespace Threading

template<typename Task>
using ThreadPool = Threading::ThreadPool<ConcurrentQueue<Task>>;
