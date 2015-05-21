/**
 * @file gpg/real_time_multiplayer_manager.h
 * @copyright Copyright 2014 Google Inc. All Rights Reserved.
 * @brief Entry points for Play Games RealTime Multiplayer functionality.
 */

#ifndef GPG_REAL_TIME_ROOM_H_
#define GPG_REAL_TIME_ROOM_H_

#ifndef __cplusplus
#error Header file supports C++ only
#endif  // __cplusplus

#include <memory>
#include <vector>
#include "gpg/common.h"
#include "gpg/game_services.h"
#include "gpg/multiplayer_invitation.h"
#include "gpg/player.h"
#include "gpg/turn_based_match.h"
#include "gpg/turn_based_match_config.h"
#include "gpg/types.h"

namespace gpg {

class RealTimeRoomImpl;

/**
 * A data structure containing the current state of a real_time multiplayer
 *room.
 *
 * @ingroup ValueType
 */
class GPG_EXPORT RealTimeRoom {
 public:
  RealTimeRoom();

  /**
   * Constructs a <code>RealTimeRoom</code> from a <code>shared_ptr</code> to
   * a <code> RealTimeRoomImpl</code>.
   * Intended for internal use by the API.
   */
  explicit RealTimeRoom(std::shared_ptr<RealTimeRoomImpl const> impl);

  /**
   * Creates a copy of an existing <code>RealTimeRoom</code>.
   */
  RealTimeRoom(RealTimeRoom const &copy_from);

  /**
   * Moves an existing <code>RealTimeRoom</code>.
   */
  RealTimeRoom(RealTimeRoom &&move_from);

  /**
   * Assigns this <code>RealTimeRoom</code> by copying from another one.
   */
  RealTimeRoom &operator=(RealTimeRoom const &copy_from);

  /**
   * Assigns this <code>RealTimeRoom</code> by moving another one into it.
   */
  RealTimeRoom &operator=(RealTimeRoom &&move_from);

  /**
   * Returns true if this <code>RealTimeRoom</code> is populated with data.
   * Must return true for the getter functions on the
   * <code>RealTimeRoom</code> object (<code>Id</code>,
   * <code>CreationTime</code>, etc...) to be usable.
   */
  bool Valid() const;

  /**
   * Returns an ID that uniquely identifies this <code>RealTimeRoom</code>.
   * Use with <code>RealTimeRoom::FetchRoom</code> to retrieve
   * this room at a later point. {@link Valid} must return true for this
   * function to be usable.
   */
  std::string const &Id() const;

  /**
   * Returns the time at which this <code>RealTimeRoom</code> was created
   * (expressed as milliseconds since the Unix epoch). {@link Valid} must return
   * true for this function to be usable.
   */
  std::chrono::milliseconds CreationTime() const;

  /**
   * Returns the participant who created this room. {@link Valid} must return
   * true for this function to be usable.
   */
  MultiplayerParticipant CreatingParticipant() const;

  /**
   * Returns the status of the room. The status determines what actions can be
   * taken on a room.  {@link Valid} must return true for this function to be
   * usable.
   */
  RealTimeRoomStatus Status() const;

  /**
   * Returns a game-specific variant identifier that can be used by a game to
   * identify different game modes. {@link Valid} must return true for
   * this function to be usable.
   */
  uint32_t Variant() const;

  /**
   * Returns a server-generated summary of the state of the room. {@link Valid}
   * must return true for this function to be usable.
   */
  std::string Description() const;

  /**
   * A vector of all participants in this room. {@link Valid} must return true
   * for this function to be usable.
   */
  std::vector<MultiplayerParticipant> Participants() const;

  /**
   * A server-generated estimate of the amount of time it will take to fill this
   * room's auto-matching slots.
   */
  Timeout AutomatchWaitEstimate() const;

  /**
   * Returns the number of available auto-matching slots for the room. This
   * number is equal to the number of auto-matching slots with which the room
   * was created, minus the number of participants who have already been added
   * via auto-matching. {@link Valid} must return true for this function to be
   * usable.
   */
  uint32_t RemainingAutomatchingSlots() const;

 private:
  friend class RealTimeRoomImpl;
  std::shared_ptr<RealTimeRoomImpl const> impl_;
};

}  // namespace gpg

#endif  // GPG_REAL_TIME_ROOM_H_
