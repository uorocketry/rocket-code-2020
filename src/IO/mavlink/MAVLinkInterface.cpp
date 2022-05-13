#include "MAVLinkInterface.h"

#include "config.h"

void MAVLinkInterface::sendHeartbeat()
{
    mavlink_message_t msg;

    // Most fields are not used by us for now, so they don't really matter.
    mavlink_msg_heartbeat_pack(MAVLINK_SYSTEM.sysid, MAVLINK_SYSTEM.compid, &msg, MAV_TYPE::MAV_TYPE_ROCKET,
                               MAV_AUTOPILOT::MAV_AUTOPILOT_INVALID, MAV_MODE_FLAG::MAV_MODE_FLAG_TEST_ENABLED, 0,
                               MAV_STATE::MAV_STATE_UNINIT);

    sendMAVLinkMessage(msg);
}
