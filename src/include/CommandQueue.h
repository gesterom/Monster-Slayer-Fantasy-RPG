#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Command.h"

class CommandQueue {
  private:
	std::queue<Command> q;
	std::mutex m;
	std::condition_variable cv;
  public:
	void push( Command com ) {
		std::unique_lock<std::mutex> locker( m );
		q.push( com );
		locker.unlock();
		cv.notify_one();
	}
	Command pop() {
		std::unique_lock<std::mutex> locker( m );
		cv.wait( locker, [&]() {
			return !q.empty();
		} );
		Command res = q.front();
		q.pop();
		return res;
	}
};
