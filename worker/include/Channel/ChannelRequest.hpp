#ifndef MS_CHANNEL_REQUEST_HPP
#define MS_CHANNEL_REQUEST_HPP

#include "common.hpp"
#include <absl/container/flat_hash_map.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace Channel
{
	// Avoid cyclic #include problem by declaring classes instead of including
	// the corresponding header files.
	class ChannelSocket;

	class ChannelRequest
	{
	public:
		enum class MethodId
		{
			WORKER_CLOSE = 1,
			WORKER_DUMP,
			WORKER_GET_RESOURCE_USAGE,
			WORKER_UPDATE_SETTINGS
		};

	private:
		static absl::flat_hash_map<std::string, MethodId> string2MethodId;

	public:
		ChannelRequest(Channel::ChannelSocket* channel, json& jsonRequest);
		virtual ~ChannelRequest();

		void Accept();
		void Accept(json& data);
		void Error(const char* reason = nullptr);
		void TypeError(const char* reason = nullptr);

	public:
		// Passed by argument.
		Channel::ChannelSocket* channel{ nullptr };
		uint32_t id{ 0u };
		std::string method;
		MethodId methodId;
		json internal;
		json data;
		// Others.
		bool replied{ false };
	};
} // namespace Channel

#endif
