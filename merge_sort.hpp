#ifndef MERGE_SORT
#define MERGE_SORT
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <functional>

#define MAX_SIZE 100
#define MAX_THREADS 4

typedef std::size_t max_i;
using Task = std::packaged_task<void()>;
typedef std::future<void> Future;
typedef std::vector<Future> v_future;
class TaskQueue;

void mergeSort(TaskQueue& tasks, max_i *arr, max_i L, max_i R);
void mergeSort(max_i *array, std::size_t size, std::size_t threads);
void merge(max_i *arr, max_i L, max_i M, max_i R);
void thread_start(std::packaged_task<void(max_i*,max_i,max_i)>& task, max_i* arr, max_i L, max_i R);
void print(max_i* arr, max_i size);

class TaskQueue {
private:
    std::queue<Task> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_closed = false;
public:
    void push(Task task) {
        std::unique_lock lock(m_mutex);
        m_queue.push(std::move(task));
        lock.unlock();
        m_cv.notify_all();
    }
    bool run() {
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [this]{ return !m_queue.empty() || m_closed; });
        if (!m_queue.empty()) {
            auto task = std::move(m_queue.front());
            m_queue.pop();
            const bool result = !m_closed || !m_queue.empty();
            lock.unlock();
            m_cv.notify_all();
            task();
            return result;
        } else {
            return !m_closed;
        }
    }
    void close() {
        std::unique_lock lock(m_mutex);
        m_closed = true;
        lock.unlock();
        m_cv.notify_all();
    }
};

class Merge_sort {
private:
    TaskQueue m_taskqueue;
    max_i* m_arr;
    std::vector<Task> m_tasks;
    v_future m_future;
    std::vector<std::thread> m_trheads;
public:
/* коструктор по умолчанию в качестве примера
сам сгенерирует массив на 100 рандомных элементов и сделает мерж
в 4 потока*/
/*
    Merge_sort() {
        max_i sys_count = 10;
        while (sys_count) {
            m_arr = new(std::nothrow) max_i[MAX_SIZE];
            if (m_arr) {
                //генерируем и печатаем массив по 10 в строке
                max_i str = 0;
                for (max_i i = 0; i < MAX_SIZE; ++i) {
                    m_arr[i] = rand() % 100;
                    std::cout << m_arr[i] << " ";
                    ++str;
                    if (str == 10) {
                        std::cout << std::endl;
                        str = 0;
                    }
                }

                //заталкиваем в вектор 4 задачи и получаем футуры
                //+ 3 для последних мержов
                for (max_i i = 0; i < MAX_THREADS; ++i) {
                    m_tasks.push_back(Task(mergeSort));
                    m_future.push_back(m_tasks[i].get_future());
                }
                //запучкаем потоки
                for (max_i i = 0; i < MAX_THREADS; ++i) {
                    m_trheads.push_back(std::thread(std::move(m_tasks[i]), m_arr, i * (MAX_SIZE/MAX_THREADS), (i + 1) * (MAX_SIZE/MAX_THREADS) - 1));
                }

                for (max_i i = 0; i < MAX_THREADS; ++i) {
                    if (m_trheads[i].joinable()) {
                        m_trheads[i].join();
                    }
                }
                //final merge
                merge(m_arr, 0, (MAX_SIZE / 2 - 1) / 2, MAX_SIZE / 2 - 1);
                merge(m_arr, MAX_SIZE / 2,  MAX_SIZE/2 + (MAX_SIZE-1-MAX_SIZE/2)/2, MAX_SIZE - 1);
                merge(m_arr, 0, (MAX_SIZE - 1)/2, MAX_SIZE - 1);
                std::cout << std::endl;
                print(m_arr, MAX_SIZE);
                break;
            }
            --sys_count;
        }
            if (!sys_count) {
                std::cout << "No heap space!" << std::endl;
            }
    }
*/
    Merge_sort(std::size_t* arr, std::size_t arr_size, std::size_t threads) {
        
    }

    ~Merge_sort() {
        delete [] m_arr;
    }
};
#endif