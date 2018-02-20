#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_INTERNAL_CHANNELSTHREAD_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_INTERNAL_CHANNELSTHREAD_HPP

#include "../Session.hpp"

#include <cutehmi/Error.hpp>

#include <QThread>

#include <memory>

namespace cutehmi {
namespace authssh {

class AbstractChannel;

namespace internal {

class ChannelsThread:
	protected QThread
{
	Q_OBJECT

	typedef QThread Parent;

	public:
//		struct Error:
//			public base::Error
//		{
//			enum : int {
//				SESSION_SWITCH = base::Error::SUBCLASS_BEGIN
//			};

//			using base::Error::Error;

//			QString str() const;
//		};

		explicit ChannelsThread(QObject * parent = 0);

		~ChannelsThread() override;

		using Parent::isRunning;

		using Parent::wait;

		void start(Session * session);

		void addChannel(std::unique_ptr<AbstractChannel> channel);

//		void pushSession(Session * session);

	public slots:
		void quit();

	protected:
		void run() override;

	private:
		typedef QList<AbstractChannel *> ChannelsContainer;

		ChannelsContainer m_channels;
		Session * m_session;
};

}
}
}

#endif // FORWARDCHANNELTHREAD_HPP
