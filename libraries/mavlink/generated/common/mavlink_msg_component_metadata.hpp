// MESSAGE COMPONENT_METADATA support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief COMPONENT_METADATA message
 *
 * 
        Component metadata message, which may be requested using MAV_CMD_REQUEST_MESSAGE.
        
        This contains the MAVLink FTP URI and CRC for the component's general metadata file.
        The file must be hosted on the component, and may be xz compressed.
        The file CRC can be used for file caching.
        
        The general metadata file can be read to get the locations of other metadata files (COMP_METADATA_TYPE) and translations, which may be hosted either on the vehicle or the internet.
        For more information see: https://mavlink.io/en/services/component_information.html.
        
        Note: Camera components should use CAMERA_INFORMATION instead, and autopilots may use both this message and AUTOPILOT_VERSION.
      
 */
struct COMPONENT_METADATA : mavlink::Message {
    static constexpr msgid_t MSG_ID = 397;
    static constexpr size_t LENGTH = 108;
    static constexpr size_t MIN_LENGTH = 108;
    static constexpr uint8_t CRC_EXTRA = 182;
    static constexpr auto NAME = "COMPONENT_METADATA";


    uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot). */
    uint32_t file_crc; /*<  CRC32 of the general metadata file. */
    std::array<char, 100> uri; /*<  MAVLink FTP URI for the general metadata file (COMP_METADATA_TYPE_GENERAL), which may be compressed with xz. The file contains general component metadata, and may contain URI links for additional metadata (see COMP_METADATA_TYPE). The information is static from boot, and may be generated at compile time. The string needs to be zero terminated. */


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
        ss << "  file_crc: " << file_crc << std::endl;
        ss << "  uri: \"" << to_string(uri) << "\"" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << time_boot_ms;                  // offset: 0
        map << file_crc;                      // offset: 4
        map << uri;                           // offset: 8
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> time_boot_ms;                  // offset: 0
        map >> file_crc;                      // offset: 4
        map >> uri;                           // offset: 8
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
