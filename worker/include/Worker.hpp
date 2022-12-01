#ifndef MS_WORKER_HPP
#define MS_WORKER_HPP

#include "common.hpp"
#include "Channel/ChannelRequest.hpp"
#include "Channel/ChannelSocket.hpp"
#include "PayloadChannel/Notification.hpp"
#include "PayloadChannel/PayloadChannelRequest.hpp"
#include "PayloadChannel/PayloadChannelSocket.hpp"
#include "handles/SignalsHandler.hpp"
#include <absl/container/flat_hash_map.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Worker : public Channel::ChannelSocket::Listener,
               public PayloadChannel::PayloadChannelSocket::Listener,
               public SignalsHandler::Listener
{
public:
	explicit Worker(Channel::ChannelSocket* channel, PayloadChannel::PayloadChannelSocket* payloadChannel);
	~Worker();

private:
	void Close();
	void FillJson(json& jsonObject) const;
	void FillJsonResourceUsage(json& jsonObject) const;

	/* Methods inherited from Channel::ChannelSocket::RequestHandler. */
public:
	void HandleRequest(Channel::ChannelRequest* request) override;

	/* Methods inherited from Channel::ChannelSocket::Listener. */
public:
	void OnChannelClosed(Channel::ChannelSocket* channel) override;

	/* Methods inherited from PayloadChannel::PayloadChannelSocket::RequestHandler. */
public:
	void HandleRequest(PayloadChannel::PayloadChannelRequest* request) override;

	/* Methods inherited from PayloadChannel::PayloadChannelSocket::NotificationHandler. */
public:
	void HandleNotification(PayloadChannel::Notification* notification) override;

	/* Methods inherited from PayloadChannel::PayloadChannelSocket::Listener. */
public:
	void OnPayloadChannelClosed(PayloadChannel::PayloadChannelSocket* payloadChannel) override;

	/* Methods inherited from SignalsHandler::Listener. */
public:
	void OnSignal(SignalsHandler* signalsHandler, int signum) override;

private:
	// Passed by argument.
	Channel::ChannelSocket* channel{ nullptr };
	PayloadChannel::PayloadChannelSocket* payloadChannel{ nullptr };
	// Allocated by this.
	SignalsHandler* signalsHandler{ nullptr };
	// Others.
	bool closed{ false };
};

#endif
