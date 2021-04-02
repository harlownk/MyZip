// Nicholas Harlow

#ifndef SRC_UTIL_CONCURRENTQUEUE_H_
#define SRC_UTIL_CONCURRENTQUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

namespace util {

template <typename T>
class ConcurrentQueue {
 public:
  ConcurrentQueue() {
    this->workQueue_ = new std::queue<T>();
    this->mutex_ = new std::recursive_mutex();
    this->lock_ = new std::unique_lock<std::recursive_mutex>(*this->mutex_, std::defer_lock);
    this->cv_ = new std::condition_variable_any();
  }

  ~ConcurrentQueue() {
    delete(this->workQueue_);
    delete(this->lock_);
    delete(this->mutex_);
    delete(this->cv_);
  }

  void add(T item) {
    this->lock_->lock();
    this->workQueue_->push(item);
    this->lock_->unlock();
  }

  T remove() {
    this->lock_->lock();
    T result = this->workQueue_->front();
    this->workQueue_->pop();
    this->lock_->unlock();
    return result;
  }

  std::condition_variable_any *getConditionVariable() {
    return this->cv_;
  }

  std::recursive_mutex *getLock() {
    return this->mutex_;
  }

  bool isEmpty() {
    this->lock_->lock();
    bool result = this->workQueue_->empty();
    this->lock_->unlock();
    return result;
  };

 private:
  std::queue<T> *workQueue_;
  std::recursive_mutex *mutex_;
  std::unique_lock<std::recursive_mutex> *lock_;  // Requires mutex to be initialized.
  std::condition_variable_any *cv_;
};  // class ConcurrentQueue

} // namespace util

#endif //SRC_UTIL_CONCURRENTQUEUE_H_