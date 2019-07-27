#pragma once

#include <algorithm>
#include <functional>
#include <future>
#include <string>
#include <unordered_map>
#include <vector>

namespace EEPP
{

/**
 * @brief Event emitter class.
 * 
 * @tparam CallbackType The type of arguments passed to the on() callback. Example: `<int, float> -> void(int, float)`
 */
template <typename... Args>
class EventEmitter
{
private:
	typedef std::function<void(Args...)> Callback;

public:
	EventEmitter()
	{
	}

	virtual ~EventEmitter()
	{
	}

	void on(std::string event, std::function<void(Args...)> callback)
	{
		//Append the callback to the callback map.
		mCallbacks[event].push_back(callback);
	}

protected:
	void emit(std::string event, Args&&... args)
	{
		// Get the list of event callbacks.
		std::vector<Callback>& callbacks = mCallbacks[event];
		for (auto& callback : callbacks)
		{
			callback(args...);
		}
	}

private:
	// Events and their associated callbacks.
	std::unordered_map<std::string, std::vector<Callback>> mCallbacks;
};

}