//
// Created by zwl on 24-9-11.
//

// 饿汉模式
class singletone {
public:
    static singletone &instance() {}
private:
    singletone() {}
    ~singletone() {}
    singletone(singletone &) {}
    singletone &operator=(singletone &) {}

private:
    static singletone* my_instance;
};

singletone* singletone::my_instance = new singletone;


// 懒汉模式 静态局部变量
// /*
// 静态局部队列对象，并且将这个对象作为了唯一的单例实例。使用这种方式之所以是线程安全的，是因为在C++11标准中有如下规定，并且这个操作是在编译时由编译器保证的：
//
// 如果指令逻辑进入一个未被初始化的声明变量，所有并发执行应当等待该变量完成初始化。
//  */
class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        static TaskQueue taskQ;
        return &taskQ;
    }
    void print()
    {
        cout << "hello, world!!!" << endl;
    }

private:
    TaskQueue() = default;
};

// 原子变量

class TaskQueue
{
public:
    // = delete 代表函数禁用, 也可以将其访问权限设置为私有
    TaskQueue(const TaskQueue& obj) = delete;
    TaskQueue& operator=(const TaskQueue& obj) = delete;
    static TaskQueue* getInstance()
    {
        TaskQueue* queue = m_taskQ.load();
        if (queue == nullptr)
        {
            // m_mutex.lock();  // 加锁: 方式1
            lock_guard<mutex> locker(m_mutex);  // 加锁: 方式2
            queue = m_taskQ.load();
            if (queue == nullptr)
            {
                queue = new TaskQueue;
                m_taskQ.store(queue);
            }
            // m_mutex.unlock();
        }
        return queue;
    }

    void print()
    {
        cout << "hello, world!!!" << endl;
    }
private:
    TaskQueue() = default;
    static atomic<TaskQueue*> m_taskQ;
    static mutex m_mutex;
};
atomic<TaskQueue*> TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;


