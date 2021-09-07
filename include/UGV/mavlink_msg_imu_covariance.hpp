// MESSAGE IMU_COVARIANCE support class

#pragma once

namespace mavlink {
namespace UGV {
namespace msg {

/**
 * @brief IMU_COVARIANCE message
 *
 * The IMU readings for the usual 9DOF sensor setup and associated covariance matrices. This message should contain the scaled values to the described units
 */
struct IMU_COVARIANCE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 500;
    static constexpr size_t LENGTH = 132;
    static constexpr size_t MIN_LENGTH = 132;
    static constexpr uint8_t CRC_EXTRA = 128;
    static constexpr auto NAME = "IMU_COVARIANCE";


    uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot). */
    int16_t xacc; /*< [mG] X acceleration */
    int16_t yacc; /*< [mG] Y acceleration */
    int16_t zacc; /*< [mG] Z acceleration */
    int16_t xgyro; /*< [mrad/s] Angular speed around X axis */
    int16_t ygyro; /*< [mrad/s] Angular speed around Y axis */
    int16_t zgyro; /*< [mrad/s] Angular speed around Z axis */
    int16_t xmag; /*< [mgauss] X Magnetic field */
    int16_t ymag; /*< [mgauss] Y Magnetic field */
    int16_t zmag; /*< [mgauss] Z Magnetic field */
    std::array<float, 9> acc_cov; /*< [-] Covariance matrix for accelerometer */
    std::array<float, 9> gyro_cov; /*< [-] Covariance matrix for gyroscope */
    std::array<float, 9> mag_cov; /*< [-] Covariance matrix for magnetometer */
    int16_t temperature; /*< [cdegC] Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C). */


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
        ss << "  xacc: " << xacc << std::endl;
        ss << "  yacc: " << yacc << std::endl;
        ss << "  zacc: " << zacc << std::endl;
        ss << "  xgyro: " << xgyro << std::endl;
        ss << "  ygyro: " << ygyro << std::endl;
        ss << "  zgyro: " << zgyro << std::endl;
        ss << "  xmag: " << xmag << std::endl;
        ss << "  ymag: " << ymag << std::endl;
        ss << "  zmag: " << zmag << std::endl;
        ss << "  acc_cov: [" << to_string(acc_cov) << "]" << std::endl;
        ss << "  gyro_cov: [" << to_string(gyro_cov) << "]" << std::endl;
        ss << "  mag_cov: [" << to_string(mag_cov) << "]" << std::endl;
        ss << "  temperature: " << temperature << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << time_boot_ms;                  // offset: 0
        map << acc_cov;                       // offset: 4
        map << gyro_cov;                      // offset: 40
        map << mag_cov;                       // offset: 76
        map << xacc;                          // offset: 112
        map << yacc;                          // offset: 114
        map << zacc;                          // offset: 116
        map << xgyro;                         // offset: 118
        map << ygyro;                         // offset: 120
        map << zgyro;                         // offset: 122
        map << xmag;                          // offset: 124
        map << ymag;                          // offset: 126
        map << zmag;                          // offset: 128
        map << temperature;                   // offset: 130
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> time_boot_ms;                  // offset: 0
        map >> acc_cov;                       // offset: 4
        map >> gyro_cov;                      // offset: 40
        map >> mag_cov;                       // offset: 76
        map >> xacc;                          // offset: 112
        map >> yacc;                          // offset: 114
        map >> zacc;                          // offset: 116
        map >> xgyro;                         // offset: 118
        map >> ygyro;                         // offset: 120
        map >> zgyro;                         // offset: 122
        map >> xmag;                          // offset: 124
        map >> ymag;                          // offset: 126
        map >> zmag;                          // offset: 128
        map >> temperature;                   // offset: 130
    }
};

} // namespace msg
} // namespace UGV
} // namespace mavlink
