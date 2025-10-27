#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>
#include <utility>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size) : buffer_size_(size), is_closed_(false) {}[cite:8]

        void Send(T value) {
        std::unique_lock<std::mutex> lock(mtx_); [cite:4, 6]

            if (is_closed_) {
                throw std::runtime_error("Send on closed channel"); [cite:13]
            }

        cv_not_full_.wait(lock, [this]() {
            return queue_.size() < buffer_size_ || is_closed_;
            }); [cite:9]

                if (is_closed_) {
                    throw std::runtime_error("Send on closed channel"); [cite:13]
                }

            queue_.push(std::move(value)); [cite:10]
                cv_not_empty_.notify_one();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> lock(mtx_); [cite:4, 6]

            cv_not_empty_.wait(lock, [this]() {
            return !queue_.empty() || is_closed_;
                }); [cite:10]

                    if (queue_.empty() && is_closed_) {
                        return { T(), false }; [cite:14]
                    }

                T value = std::move(queue_.front()); [cite:11]
                    queue_.pop();

                cv_not_full_.notify_one();
                return { std::move(value), true }; [cite:14]
    }

    void Close() {
        std::lock_guard<std::mutex> lock(mtx_); [cite:4]
            is_closed_ = true; [cite:13]
            cv_not_full_.notify_all();
        cv_not_empty_.notify_all();
    }

private:
    std::queue<T> queue_; [cite:8]
        size_t buffer_size_;
    bool is_closed_;
    std::mutex mtx_;
    std::condition_variable cv_not_full_;
    std::condition_variable cv_not_empty_;
};

#endif // BUFFERED_CHANNEL_H_