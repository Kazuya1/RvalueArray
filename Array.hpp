#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "MyInt.hpp"
#include <time.h>

namespace cs540 {
    class Array{
        friend std::ostream& operator<<(std::ostream& os, const Array& obj){
            if(obj.len!=0){
                int count = 0;
                os<<(*(obj.arr[count++]));
                while(count<obj.len) os<<", "<<(*(obj.arr[count++]));
            }
            return os;
        }
        
    public:
        Array(){
            //            std::cout<<"Empty constructor"<<std::endl;
            arr = nullptr;
            len = 0;
        }
        
        Array(std::initializer_list<int> values){
            //            std::cout<<"Normal list constructor"<<std::endl;
            len = values.size();
            arr = new MyInt*[len];
            int count = 0;
            for (int value : values) arr[count++] = new MyInt(value);
        }
        
        Array(const Array& obj){
            //            std::cout<<"Copy constructor"<<std::endl;
            copy(obj);
        }
        
        Array(Array&& obj){
            //            std::cout<<"Move constructor"<<std::endl;
            len = obj.len;
            arr = obj.arr;
            obj.len = 0;
            obj.arr = nullptr;
        }
        
        ~Array(){
            clean();
        }
        
        Array& operator=(const Array& obj){
            //            std::cout<<"Copy assignment"<<std::endl;
            if(this!=&obj){
                clean();
                copy(obj);
            }
            return *this;
        }
        
        Array& operator=(Array&& obj){
            //            std::cout<<"Move assignment"<<std::endl;
            if(this!=&obj){
                len = obj.len;
                arr = obj.arr;
                obj.arr = nullptr;
                obj.len = 0;
            }
            return *this;
        }
        
        static void move_performance_test(){
            int cycle = 1000;
            clock_t t_start,t_end;
            Array a1{1, 2, 3};
            t_start = clock() ;
            for(int i=0;i<cycle;i++) Array a2{std::move(a1)};
            t_end = clock();
            int diff1 = difftime(t_end,t_start);
            Array a3{1, 2, 3};
            t_start = clock() ;
            for(int i=0;i<cycle;i++) Array a4{a3};
            t_end = clock();
            int diff2 = difftime(t_end,t_start);
            std::cerr<<"The move constructor saves "<<diff2-diff1<<"ms for "<<cycle<<" cycles."<<std::endl;
            
            
            t_start = clock();
            for(int i=0;i<cycle;i++){
                Array a1{1, 2, 3};
                Array a2;
                a2 = std::move(a1);
            }
            t_end = clock();
            int diff3 = difftime(t_end,t_start);
            t_start = clock() ;
            for(int i=0;i<cycle;i++) {
                Array a3{1, 2, 3};
                Array a4;
                a4 = a3;
            }
            t_end = clock();
            int diff4 = difftime(t_end,t_start);
            std::cerr<<"The move assignment saves "<<diff4-diff3<<"ms for "<<cycle<<" cycles."<<std::endl;
        }
        
    private:
        void clean(){
            if(arr!=nullptr){
                for (int i=0;i<len;i++) delete arr[i];
                delete[] arr;
            }
        }
        
        void copy(const Array& obj){
            if(obj.len!=0){
                len = obj.len;
                arr = new MyInt*[len];
                int count = 0;
                while(count<len) {
                    arr[count] = new MyInt;
                    memcpy(arr[count], obj.arr[count], sizeof(MyInt));
                    count++;
                }
            }else{
                len = 0;
                arr = nullptr;
            }
        }
        
        MyInt** arr;
        size_t len;
    };
}
#endif
