#pragma  once
#include <iostream>
#include <string>
#include <atomic>
#include <mutex>

template <typename T>
class SingletonFactory
{
public:
	// DCLP + std::atomic ʵ�ֵ����̰߳�ȫ+ԭ�Ӳ���
	static T* GetInstance()
	{
		T* Temp = s_Instance.load();
		if (Temp == nullptr)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			Temp = s_Instance.load();
			if (Temp == nullptr)
			{
				Temp = new T;
				s_Instance.store(Temp);

			}
		}

		return Temp;
	}

	static void SetInstance(T* Instance)
	{
		T* Temp = s_Instance.load();
		if (Temp == nullptr)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			Temp = s_Instance.load();
			if (Temp == nullptr)
			{
				s_Instance.store(Instance);
			}
		}
	}

protected:
	SingletonFactory<T>() { }
	~SingletonFactory<T>() { }

private:
	static std::atomic<T*> s_Instance;
	static std::mutex m_Mutex;

	// ��ֹ��������
	SingletonFactory<T>(const SingletonFactory<T>&);
	const SingletonFactory<T>& operator=(const SingletonFactory<T>&);
};

template <typename T>
std::atomic<T*> SingletonFactory<T>::s_Instance;
template <typename T>
std::mutex SingletonFactory<T>::m_Mutex;