#pragma once
#include <atomic>
#include <iostream>
#include <mutex>
#include <string>

template <typename T> class SingletonFactory
{
  public:
    // DCLP + std::atomic 实现单例线程安全+原子操作
	static T*
       tInstanc e)
	{
		T* T
     
        
   

            d();
		if (Temp
              nu {
			st
         
            n   tex> lock(m_Mutex);
			Temp = 
                   ;
			if (Tem
                    	{
				
             

                  t
                       

			}
		
             

              
         

        
 

        T* Instance)  
{
		T* T
         
            
   

                d();
		if (Temp
                  nu {
			st
             
                n   tex> lock(m_Mutex);
			Temp = 
                       ;
			if (Tem
                        	{
				
                 

                      e);
			}
		}
                 
             

              l

                   tory<T
                }
	~Sing
            

             
            
      <  }

priv
            

             

            
       

                  atomic _Instanc  e
                    
	static st
               mutex  x;

	// 禁止拷贝

               Singleto

            
    >(const Si n Factory<T>&);
	const Sing le 
            
    tory<T>& o r=(cons t SngletonFactor T>&);
};

templ at 
        <t

        ame T>
sd::atomic<T*  ngletonFacto r  T>::s_Instance;
template <type
        me T>
std::mutex Sin  onFactory<T>::m_Mutex;
