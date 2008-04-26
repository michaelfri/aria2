/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_DEFAULT_BT_MESSAGE_DISPATCHER_H_
#define _D_DEFAULT_BT_MESSAGE_DISPATCHER_H_

#include "BtMessageDispatcher.h"
#include "a2time.h"

namespace aria2 {

class BtContext;
class PeerStorage;
class PieceStorage;
class BtMessage;
class BtMessageFactory;
class Peer;
class Piece;
class Logger;

class DefaultBtMessageDispatcher : public BtMessageDispatcher {
private:
  int32_t cuid;
  std::deque<SharedHandle<BtMessage> > messageQueue;
  std::deque<RequestSlot> requestSlots;
  SharedHandle<BtContext> btContext;
  SharedHandle<PeerStorage> peerStorage;
  SharedHandle<PieceStorage> pieceStorage;
  WeakHandle<BtMessageFactory> messageFactory;
  SharedHandle<Peer> peer;
  unsigned int maxUploadSpeedLimit;
  time_t requestTimeout;
  Logger* logger;
public:
  DefaultBtMessageDispatcher();

  virtual ~DefaultBtMessageDispatcher();
  
  virtual void addMessageToQueue(const SharedHandle<BtMessage>& btMessage);

  virtual void addMessageToQueue(const std::deque<SharedHandle<BtMessage> >& btMessages);

  virtual void sendMessages();

  virtual void doCancelSendingPieceAction(size_t index, uint32_t begin, size_t length);

  virtual void doCancelSendingPieceAction(const SharedHandle<Piece>& piece);

  virtual void doAbortOutstandingRequestAction(const SharedHandle<Piece>& piece);

  virtual void doChokedAction();

  virtual void doChokingAction();

  virtual void checkRequestSlotAndDoNecessaryThing();

  virtual bool isSendingInProgress();

  virtual size_t countMessageInQueue() {
    return messageQueue.size();
  }

  virtual size_t countOutstandingRequest();

  virtual bool isOutstandingRequest(size_t index, size_t blockIndex);

  virtual RequestSlot getOutstandingRequest(size_t index, uint32_t begin, size_t length);

  virtual void removeOutstandingRequest(const RequestSlot& slot);

  virtual void addOutstandingRequest(const RequestSlot& requestSlot);

  virtual size_t countOutstandingUpload();

  std::deque<SharedHandle<BtMessage> >& getMessageQueue();

  RequestSlots& getRequestSlots();

  void setPeer(const SharedHandle<Peer>& peer);

  void setBtContext(const SharedHandle<BtContext>& btContext);

  void setBtMessageFactory(const WeakHandle<BtMessageFactory>& factory);

  void setCuid(int32_t cuid) {
    this->cuid = cuid;
  }

  void setMaxUploadSpeedLimit(unsigned int maxUploadSpeedLimit) {
    this->maxUploadSpeedLimit = maxUploadSpeedLimit;
  }

  void setRequestTimeout(time_t requestTimeout) {
    this->requestTimeout = requestTimeout;
  }

};

typedef SharedHandle<DefaultBtMessageDispatcher> DefaultBtMessageDispatcherHandle;

} // namespace aria2

#endif // _D_DEFAULT_BT_MESSAGE_DISPATCHER_H_
