#pragma once

#include <map>
#include <memory>
#include <mutex>
#include "packetsender.h"

class Buffer
{
  using PktSender = std::shared_ptr<PaketSender>;

public:
  Buffer();
  ~Buffer();

  void operator()();
  void processData();
  void addSender(const std::string &callid, std::shared_ptr<PaketSender> sender);
  void removeSender(const std::string &callid);
  void clearSenders();
  int  senderNumber();

private:
  std::map<std::string, PktSender> senders_;
  std::mutex destsmutex_;
};