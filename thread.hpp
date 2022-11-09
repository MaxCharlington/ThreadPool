#pragma once

#include <thread>

namespace Threading
{

class Thread
{
public:
    template<typename Job, typename Arg>
    Thread(Job&& job, Arg& arg, unsigned core, int policy = SCHED_RR, int priority = 99)
        : m_thread{std::forward<Job>(job), std::ref(arg)}
    {
        bind_core(core);
        set_priority(policy, priority);
    }

private:
    void bind_core(unsigned core)
    {
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(core, &cpuset);
        pthread_setaffinity_np(m_thread.native_handle(), sizeof(cpu_set_t), &cpuset);
    }

    void set_priority(int policy, int priority)
    {
        sched_param sched;
        int policy_;
        pthread_getschedparam(m_thread.native_handle(), &policy_, &sched);
        sched.sched_priority = priority;
        pthread_setschedparam (m_thread.native_handle(), policy, &sched);
    }

    std::jthread m_thread;
};

}  //namespace Threading
