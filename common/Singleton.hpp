#include <iostream>
#include <string>
#include <atomic>
#include <mutex>

template <typename T>
class SingletonFactory
{
public:
	// DCLP + std::atomic 实现单例线程安全+原子操作
	static T* GetInstance()
	{
		T* Temp = s_Instance.load();
		if (Temp == nullptr)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			Temp = s_Instance.load();
			if (Temp == nullptr)
			{
				Temp = new T;
				s_Instance.store(Temp);

			}
		}

		return Temp;
	}

protected:
	SingletonFactory<T>() { }
	~SingletonFactory<T>() { }

private:
	static std::atomic<T*> s_Instance;
	static std::mutex m_Mutex;

	// 禁止拷贝操作
	SingletonFactory<T>(const SingletonFactory<T>&);
	const SingletonFactory<T>& operator=(const SingletonFactory<T>&);
};

template <typename T>
std::atomic<T*> SingletonFactory<T>::s_Instance;
template <typename T>
std::mutex SingletonFactory<T>::m_Mutex;