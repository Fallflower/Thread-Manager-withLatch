#pragma once
#include <iostream>
#include <thread>
#include <latch>
#include <chrono>
#include <random>
using namespace std::chrono_literals;

class ThreadManager {
private:
	int threads_num;
	std::latch latch;
	std::vector<std::jthread> threads;

	void f(int id, int t)
	{
		std::this_thread::sleep_for(std::chrono::seconds(t));
		std::cout << std::format("Thread {} completed the task after {}s, waiting for others\n", id, t);
		latch.arrive_and_wait();
		std::cout << std::format("Thread {} exit\n", id);
	}

public:
	ThreadManager(int num_threads) : threads_num(num_threads), latch(num_threads) {}

	void demo(int T) {
		std::random_device rd;  // ʹ������豸��������
		std::mt19937 gen(rd()); // ʹ��÷ɭ��ת�㷨���������
		std::uniform_int_distribution<> dis(1, T); // ����һ�����ȷֲ�����Χ��1��10

		for (int i = 0; i < threads_num; i++) {
			int t = dis(gen);
			threads.emplace_back(&ThreadManager::f, this, i, t);
		}
	}

};

