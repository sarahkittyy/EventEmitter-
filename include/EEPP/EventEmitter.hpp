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
 * @tparam Args The type of arguments passed to the on() callback. Example: `<int, float> -> void(int, float)`
 */
template <typename... Args>
class EventEmitter
{
private:
	/// For readablility.
	typedef std::function<void(Args...)> Callback;

public:
	/**
	 * @brief Here for inheritability.
	 * 
	 */
	virtual ~EventEmitter()
	{
	}

	/**
	 * @brief Attach a callback to an event.
	 * 
	 * @param event The event emitted.
	 * @param callback The callback to run when that event fires.
	 */
	void on(std::string event, std::function<void(Args...)> callback)
	{
		//Append the callback to the callback map.
		mCallbacks[event].push_back(callback);
	}

protected:
	/**
	 * @brief Emit an event to all subscribed callbacks.
	 * 
	 * @param event The name of the event.
	 * @param args The args to pass to the callback.
	 */
	void emit(std::string event, Args... args)
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