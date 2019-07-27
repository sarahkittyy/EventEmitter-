# EventEmitter++

NodeJS-esque EventEmitter for C++

## Example

```cpp
#include <functional>
#include <future>
#include <iostream>
#include <queue>
#include <string>
#include "EEPP/EventEmitter.hpp"

/**
 * @brief Runs an async task to listen for numbers. Emits the "doubled" event
 * with the doubled number on every recieved number.
 * 
 */
class Doubler : public EEPP::EventEmitter<float>
{
public:
	Doubler()
		: mRunning(true)
	{
		// Launch the async listener.
		mTask = std::async(std::bind(&Doubler::listenForNumbers, this));
	}

	/**
	 * @brief Send a number to the listening task.
	 * 
	 * @param number The number to send.
	 */
	void sendNumber(float number)
	{
		// Push the number to the queue.
		mNumbers.push(number);
	}

	/**
	 * @brief Tells the listening task to stop and waits for it to terminate.
	 * 
	 */
	void wait()
	{
		mRunning = false;
		mTask.wait();
	}

private:
	/// Listens for numbers, emitting the doubled event when one is received.
	void listenForNumbers()
	{
		// Run until all numbers are gone and we are told to stop.
		while (mRunning || mNumbers.size() > 0)
		{
			while (mNumbers.size() > 0)
			{
				float number = mNumbers.front();
				mNumbers.pop();   // Pop the number.

				// Double the number.
				float doubled = number * 2;

				// Emit the newly doubled number.
				emit("doubled", doubled);
			}
		}
	}

	std::future<void> mTask;
	std::queue<float> mNumbers;
	bool mRunning;
};

int main()
{
	// Create the doubler instance.
	Doubler doubler;
	// Attach a listener.
	doubler.on("doubled", [](float value) {
		std::cout << "Number doubled to " << value << "\n";
	});
	// Send some numbers.
	for (float i = 0; i < 5; i += 0.5f)
	{
		doubler.sendNumber(i);
	}

	// Wait for the doubler to finish.
	doubler.wait();
	return 0;
}

/*
Output: 
Number doubled to 0
Number doubled to 1
Number doubled to 2
Number doubled to 3
Number doubled to 4
Number doubled to 5
Number doubled to 6
Number doubled to 7
Number doubled to 8
Number doubled to 9
*/
```

## Building

This project uses CMake.

```bash
mkdir build
cd build
cmake ..
make
```

## Linking

Include the `include/` directory, and link with `-leepp`

---

## Why?

Just as a fun experiment \<3