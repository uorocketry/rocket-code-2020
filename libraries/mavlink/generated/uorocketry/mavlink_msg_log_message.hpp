// MESSAGE LOG_MESSAGE support class

#pragma once

namespace mavlink {
namespace uorocketry {
namespace msg {

/**
 * @brief LOG_MESSAGE message
 *
 * A logging message.
 */
struct LOG_MESSAGE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 50001;
    static constexpr size_t LENGTH = 92;
    static constexpr size_t MIN_LENGTH = 92;
    static constexpr uint8_t CRC_EXTRA = 112;
    static constexpr auto NAME = "LOG_MESSAGE";


    uint8_t severity; /*<  Severity of the message */
    uint8_t length; /*<  The length of the log contained in data */
    std::array<uint8_t, 90> data; /*<  The actual log */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  severity: " << +severity << std::endl;
        ss << "  length: " << +length << std::endl;
        ss << "  data: [" << to_string(data) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << severity;                      // offset: 0
        map << length;                        // offset: 1
        map << data;                          // offset: 2
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> severity;                      // offset: 0
        map >> length;                        // offset: 1
        map >> data;                          // offset: 2
    }
};

} // namespace msg
} // namespace uorocketry
} // namespace mavlink
