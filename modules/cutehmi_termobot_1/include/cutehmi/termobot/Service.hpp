#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "internal/common.hpp"

#include <cutehmi/services/Service.hpp>

namespace cutehmi {
namespace termobot {

class Client;

class Service : public services::Service {
public:
  Service(const QString &name, Client *client, QObject *parent = nullptr);

protected:
  State customStart() override;

  State customStop() override;
};

} // namespace termobot
} // namespace cutehmi

#endif // SERVICE_HPP
