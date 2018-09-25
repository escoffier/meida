#pragma once

#include "buffer.h"
#include <mutex>
#include <algorithm>

//template <typename T>
class ThreadPool
{
    struct Thread_wrapper
    {
        Thread_wrapper()
        {
            thread_ = std::thread(&Thread_wrapper::run, this);
        }

        // template <class Function, class... Args>
        // Thread_wrapper(Function &&f, Args &&... args)
        // {
        //     thread_ = std::thread(std::forward<Function>(f), std::forward<Args>(args)...);
        // }

        Thread_wrapper(Thread_wrapper &&t) : thread_(std::move(t.thread_)), buffers_(std::move(t.buffers_))
        {
        }

        Thread_wrapper &operator=(const Thread_wrapper &&t) = delete;
        Thread_wrapper(const Thread_wrapper &t) = delete;
        Thread_wrapper &operator=(const Thread_wrapper &t) = delete;

        void run()
        {
            while (true)
            {
                std::lock_guard<std::mutex> lk(mutex_);
                for (auto &b : buffers_)
                {
                    b.second->processData();
                }
            }
        }

        void addBuffer(const std::string &id, std::shared_ptr<Buffer> buffer)
        {
            std::lock_guard<std::mutex> lk(mutex_);
            buffers_.emplace(id, buffer);
        }

        size_t bufferSize()
        {
            std::lock_guard<std::mutex> lk(mutex_);
            return buffers_.size();
        }

        std::shared_ptr<Buffer> findBuffer(const std::string &id)
        {
            std::lock_guard<std::mutex> lk(mutex_);
            auto buf = buffers_.find(id);
            if (buf != buffers_.end())
                return buf->second;
            return std::shared_ptr<Buffer>();
        }

        void removeBuffer(const std::string &id)
        {
            std::lock_guard<std::mutex> lk(mutex_);

            auto buf = buffers_.find(id);
            if (buf != buffers_.end())
            {
                if (buf->second->senderNumber() != 0)
                {
                    buf->second->clearSenders();
                }

                buffers_.erase(buf);
            }
        }

        std::mutex mutex_;
        std::thread thread_;
        std::map<std::string, std::shared_ptr<Buffer>> buffers_;
    };

  public:
    ThreadPool(int n) : threads_(std::vector<Thread_wrapper>(n))
    {
    }

    void attachBuffer(std::string id, std::shared_ptr<Buffer> buffer)
    {
        auto th = std::min_element(threads_.begin(), threads_.end(), [](Thread_wrapper &a, Thread_wrapper &b) -> bool {
            return a.bufferSize() < b.bufferSize();
        });

        th->addBuffer(id, buffer);
        //min->buffers_.push_back(buffer);
    }

    std::shared_ptr<Buffer> getBuffer(const std::string &id)
    {
        for (int i = 0; i < threads_.size(); i++)
        {
            auto buf = threads_[i].findBuffer(id);
            if (buf != nullptr)
                return buf;
        }

        return std::shared_ptr<Buffer>();
    }

    void removeBuffer(const std::string &id)
    {
        for (int i = 0; i < threads_.size(); i++)
        {
            auto buf = threads_[i].findBuffer(id);
            if (buf != nullptr)
                threads_[i].removeBuffer(id);
        }
    }

    // bool addSender(const std::string &id, const std::string &callid, std::shared_ptr<PaketSender> sender)
    // {
    //     int index = getThreadIndex(id);
    //     if (index != -1)
    //         threads_[index].addSender(callid, sender);
    // }

    // int getThreadIndex(std::string id)
    // {
    //     for (int i = 0; i < threads_.size(); i++)
    //     {
    //         if (threads_[i].findBuffer(id))
    //             return i;
    //     }
    //     return -1;
    // }

  private:
    void operator()()
    {
    }

    bool shutdown_;
    std::vector<Thread_wrapper> threads_;
    //std::mutex mutex_;
};