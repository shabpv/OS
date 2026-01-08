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
    explicit BufferedChannel(int size)
        : buffer_size_(static_cast<size_t>(size)), is_closed_(false) {}

    void Send(T value) {
        std::unique_lock<std::mutex> lock(mtx_);

        cv_not_full_.wait(lock, [this]() {
            return queue_.size() < buffer_size_ || is_closed_;
        });

        if (is_closed_) {
            throw std::runtime_error("Send on closed channel");
        }

        queue_.push(std::move(value));
        cv_not_empty_.notify_one();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> lock(mtx_);

        cv_not_empty_.wait(lock, [this]() {
            return !queue_.empty() || is_closed_;
        });

        if (queue_.empty()) {
            return {T(), false};
        }

        T value = std::move(queue_.front());
        queue_.pop();
        cv_not_full_.notify_one();

        return {std::move(value), true};
    }

    void Close() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            is_closed_ = true;
        }
        cv_not_empty_.notify_all();
        cv_not_full_.notify_all();
    }

private:
    std::queue<T> queue_;
    const size_t buffer_size_;
    bool is_closed_;
    std::mutex mtx_;
    std::condition_variable cv_not_full_;
    std::condition_variable cv_not_empty_;
};

#endif // BUFFERED_CHANNEL_H_
