// MESSAGE COMPONENT_INFORMATION support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief COMPONENT_INFORMATION message
 *
 * 
        Component information message, which may be requested using MAV_CMD_REQUEST_MESSAGE.
      
 */
struct COMPONENT_INFORMATION : mavlink::Message {
    static constexpr msgid_t MSG_ID = 395;
    static constexpr size_t LENGTH = 212;
    static constexpr size_t MIN_LENGTH = 212;
    static constexpr uint8_t CRC_EXTRA = 0;
    static constexpr auto NAME = "COMPONENT_INFORMATION";


    uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot). */
    uint32_t general_metadata_file_crc; /*<  CRC32 of the general metadata file (general_metadata_uri). */
    std::array<char, 100> general_metadata_uri; /*<  MAVLink FTP URI for the general metadata file (COMP_METADATA_TYPE_GENERAL), which may be compressed with xz. The file contains general component metadata, and may contain URI links for additional metadata (see COMP_METADATA_TYPE). The information is static from boot, and may be generated at compile time. The string needs to be zero terminated. */
    uint32_t peripherals_metadata_file_crc; /*<  CRC32 of peripherals metadata file (peripherals_metadata_uri). */
    std::array<char, 100> peripherals_metadata_uri; /*<  (Optional) MAVLink FTP URI for the peripherals metadata file (COMP_METADATA_TYPE_PERIPHERALS), which may be compressed with xz. This contains data about "attached components" such as UAVCAN nodes. The peripherals are in a separate file because the information must be generated dynamically at runtime. The string needs to be zero terminated. */


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
        ss << "  time_boot_ms: " << time_boot_ms << std::endl;
        ss << "  general_metadata_file_crc: " << general_metadata_file_crc << std::endl;
        ss << "  general_metadata_uri: \"" << to_string(general_metadata_uri) << "\"" << std::endl;
        ss << "  peripherals_metadata_file_crc: " << peripherals_metadata_file_crc << std::endl;
        ss << "  peripherals_metadata_uri: \"" << to_string(peripherals_metadata_uri) << "\"" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << time_boot_ms;                  // offset: 0
        map << general_metadata_file_crc;     // offset: 4
        map << peripherals_metadata_file_crc; // offset: 8
        map << general_metadata_uri;          // offset: 12
        map << peripherals_metadata_uri;      // offset: 112
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> time_boot_ms;                  // offset: 0
        map >> general_metadata_file_crc;     // offset: 4
        map >> peripherals_metadata_file_crc; // offset: 8
        map >> general_metadata_uri;          // offset: 12
        map >> peripherals_metadata_uri;      // offset: 112
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
