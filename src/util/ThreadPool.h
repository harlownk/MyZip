#ifndef SRC_UTIL_THREADPOOL_H_
#define SRC_UTIL_THREADPOOL_H_

#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "ConcurrentQueue.h"

namespace util {

template <typename Obj, typename Fn, typename Ret>
class ThreadPool {
 public:
  ThreadPool(int numThreads) {
    this->isAlive_ = true;
    // Initialize the queue.
    this->queue_ = new util::ConcurrentQueue<std::packaged_task<Fn> *>();
    // Start up all of the threads
    for (int i = 0; i < numThreads; i++) {
      this->threads_.push_back(new std::thread(ThreadPool::threadLoop, this));
    }
  }
  
  ~ThreadPool() {
    this->isAlive_ = false;
    this->queue_->getConditionVariable()->notify_all();  // Wake all threads so they aren't blocking forever.
    // Join all the threads. The threads only complete when the threadpool is 'dead'
  }

  std::future<Ret> run(Obj *work) {
    std::packaged_task<Fn> *task = new std::packaged_task<Fn>(std::move((*work)));
    std::future<Ret> future = task->get_future();
    queue_->add(task);
    this->queue_->getConditionVariable()->notify_all();
    return future;
  }

  bool isAlive();
  
  void doWork() {
    // Block with condition variable until thtere is work in the queue/ OR return if pool is dead.
    // Execute one item of work from the queue.
    std::unique_lock<std::recursive_mutex> lock(*this->queue_->getLock(), std::defer_lock);
    lock.lock();
    while (this->queue_->isEmpty()) {
      if (!this->isAlive_) {
        lock.unlock();
        return;
      }
      this->queue_->getConditionVariable()->wait(lock);
    }
    std::packaged_task<Fn> *task = this->queue_->remove();
    lock.unlock();
    (*task)();  // The client holds the future that has the result of this call.
  }

 private:
  util::ConcurrentQueue<std::packaged_task<Fn> *> *queue_;
  std::vector<std::thread *> threads_;
  bool isAlive_;  // Only way to clean up fully is to shut down all threads. Only way to stop threds is to have them check this flag.
  static void threadLoop(ThreadPool *pool) {
    while (pool->isAlive_) {
      pool->doWork();
    }
  }
};

// template<typename Obj, typename Fn, typename Ret>


} // namespace util

#endif  // SRC_UTIL_THREADPOOL_H_