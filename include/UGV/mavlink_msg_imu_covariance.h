#pragma once
// MESSAGE IMU_COVARIANCE PACKING

#define MAVLINK_MSG_ID_IMU_COVARIANCE 500


typedef struct __mavlink_imu_covariance_t {
 uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
 float acc_cov[9]; /*< [-] Covariance matrix for accelerometer*/
 float gyro_cov[9]; /*< [-] Covariance matrix for gyroscope*/
 float mag_cov[9]; /*< [-] Covariance matrix for magnetometer*/
 int16_t xacc; /*< [mG] X acceleration*/
 int16_t yacc; /*< [mG] Y acceleration*/
 int16_t zacc; /*< [mG] Z acceleration*/
 int16_t xgyro; /*< [mrad/s] Angular speed around X axis*/
 int16_t ygyro; /*< [mrad/s] Angular speed around Y axis*/
 int16_t zgyro; /*< [mrad/s] Angular speed around Z axis*/
 int16_t xmag; /*< [mgauss] X Magnetic field*/
 int16_t ymag; /*< [mgauss] Y Magnetic field*/
 int16_t zmag; /*< [mgauss] Z Magnetic field*/
 int16_t temperature; /*< [cdegC] Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).*/
} mavlink_imu_covariance_t;

#define MAVLINK_MSG_ID_IMU_COVARIANCE_LEN 132
#define MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN 132
#define MAVLINK_MSG_ID_500_LEN 132
#define MAVLINK_MSG_ID_500_MIN_LEN 132

#define MAVLINK_MSG_ID_IMU_COVARIANCE_CRC 128
#define MAVLINK_MSG_ID_500_CRC 128

#define MAVLINK_MSG_IMU_COVARIANCE_FIELD_ACC_COV_LEN 9
#define MAVLINK_MSG_IMU_COVARIANCE_FIELD_GYRO_COV_LEN 9
#define MAVLINK_MSG_IMU_COVARIANCE_FIELD_MAG_COV_LEN 9

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_IMU_COVARIANCE { \
    500, \
    "IMU_COVARIANCE", \
    14, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_imu_covariance_t, time_boot_ms) }, \
         { "xacc", NULL, MAVLINK_TYPE_INT16_T, 0, 112, offsetof(mavlink_imu_covariance_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_INT16_T, 0, 114, offsetof(mavlink_imu_covariance_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_INT16_T, 0, 116, offsetof(mavlink_imu_covariance_t, zacc) }, \
         { "xgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 118, offsetof(mavlink_imu_covariance_t, xgyro) }, \
         { "ygyro", NULL, MAVLINK_TYPE_INT16_T, 0, 120, offsetof(mavlink_imu_covariance_t, ygyro) }, \
         { "zgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 122, offsetof(mavlink_imu_covariance_t, zgyro) }, \
         { "xmag", NULL, MAVLINK_TYPE_INT16_T, 0, 124, offsetof(mavlink_imu_covariance_t, xmag) }, \
         { "ymag", NULL, MAVLINK_TYPE_INT16_T, 0, 126, offsetof(mavlink_imu_covariance_t, ymag) }, \
         { "zmag", NULL, MAVLINK_TYPE_INT16_T, 0, 128, offsetof(mavlink_imu_covariance_t, zmag) }, \
         { "acc_cov", NULL, MAVLINK_TYPE_FLOAT, 9, 4, offsetof(mavlink_imu_covariance_t, acc_cov) }, \
         { "gyro_cov", NULL, MAVLINK_TYPE_FLOAT, 9, 40, offsetof(mavlink_imu_covariance_t, gyro_cov) }, \
         { "mag_cov", NULL, MAVLINK_TYPE_FLOAT, 9, 76, offsetof(mavlink_imu_covariance_t, mag_cov) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 130, offsetof(mavlink_imu_covariance_t, temperature) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_IMU_COVARIANCE { \
    "IMU_COVARIANCE", \
    14, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_imu_covariance_t, time_boot_ms) }, \
         { "xacc", NULL, MAVLINK_TYPE_INT16_T, 0, 112, offsetof(mavlink_imu_covariance_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_INT16_T, 0, 114, offsetof(mavlink_imu_covariance_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_INT16_T, 0, 116, offsetof(mavlink_imu_covariance_t, zacc) }, \
         { "xgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 118, offsetof(mavlink_imu_covariance_t, xgyro) }, \
         { "ygyro", NULL, MAVLINK_TYPE_INT16_T, 0, 120, offsetof(mavlink_imu_covariance_t, ygyro) }, \
         { "zgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 122, offsetof(mavlink_imu_covariance_t, zgyro) }, \
         { "xmag", NULL, MAVLINK_TYPE_INT16_T, 0, 124, offsetof(mavlink_imu_covariance_t, xmag) }, \
         { "ymag", NULL, MAVLINK_TYPE_INT16_T, 0, 126, offsetof(mavlink_imu_covariance_t, ymag) }, \
         { "zmag", NULL, MAVLINK_TYPE_INT16_T, 0, 128, offsetof(mavlink_imu_covariance_t, zmag) }, \
         { "acc_cov", NULL, MAVLINK_TYPE_FLOAT, 9, 4, offsetof(mavlink_imu_covariance_t, acc_cov) }, \
         { "gyro_cov", NULL, MAVLINK_TYPE_FLOAT, 9, 40, offsetof(mavlink_imu_covariance_t, gyro_cov) }, \
         { "mag_cov", NULL, MAVLINK_TYPE_FLOAT, 9, 76, offsetof(mavlink_imu_covariance_t, mag_cov) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 130, offsetof(mavlink_imu_covariance_t, temperature) }, \
         } \
}
#endif

/**
 * @brief Pack a imu_covariance message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param xacc [mG] X acceleration
 * @param yacc [mG] Y acceleration
 * @param zacc [mG] Z acceleration
 * @param xgyro [mrad/s] Angular speed around X axis
 * @param ygyro [mrad/s] Angular speed around Y axis
 * @param zgyro [mrad/s] Angular speed around Z axis
 * @param xmag [mgauss] X Magnetic field
 * @param ymag [mgauss] Y Magnetic field
 * @param zmag [mgauss] Z Magnetic field
 * @param acc_cov [-] Covariance matrix for accelerometer
 * @param gyro_cov [-] Covariance matrix for gyroscope
 * @param mag_cov [-] Covariance matrix for magnetometer
 * @param temperature [cdegC] Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_covariance_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_boot_ms, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag, const float *acc_cov, const float *gyro_cov, const float *mag_cov, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_COVARIANCE_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int16_t(buf, 112, xacc);
    _mav_put_int16_t(buf, 114, yacc);
    _mav_put_int16_t(buf, 116, zacc);
    _mav_put_int16_t(buf, 118, xgyro);
    _mav_put_int16_t(buf, 120, ygyro);
    _mav_put_int16_t(buf, 122, zgyro);
    _mav_put_int16_t(buf, 124, xmag);
    _mav_put_int16_t(buf, 126, ymag);
    _mav_put_int16_t(buf, 128, zmag);
    _mav_put_int16_t(buf, 130, temperature);
    _mav_put_float_array(buf, 4, acc_cov, 9);
    _mav_put_float_array(buf, 40, gyro_cov, 9);
    _mav_put_float_array(buf, 76, mag_cov, 9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN);
#else
    mavlink_imu_covariance_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;
    packet.temperature = temperature;
    mav_array_memcpy(packet.acc_cov, acc_cov, sizeof(float)*9);
    mav_array_memcpy(packet.gyro_cov, gyro_cov, sizeof(float)*9);
    mav_array_memcpy(packet.mag_cov, mag_cov, sizeof(float)*9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_COVARIANCE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_CRC);
}

/**
 * @brief Pack a imu_covariance message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param xacc [mG] X acceleration
 * @param yacc [mG] Y acceleration
 * @param zacc [mG] Z acceleration
 * @param xgyro [mrad/s] Angular speed around X axis
 * @param ygyro [mrad/s] Angular speed around Y axis
 * @param zgyro [mrad/s] Angular speed around Z axis
 * @param xmag [mgauss] X Magnetic field
 * @param ymag [mgauss] Y Magnetic field
 * @param zmag [mgauss] Z Magnetic field
 * @param acc_cov [-] Covariance matrix for accelerometer
 * @param gyro_cov [-] Covariance matrix for gyroscope
 * @param mag_cov [-] Covariance matrix for magnetometer
 * @param temperature [cdegC] Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_imu_covariance_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_boot_ms,int16_t xacc,int16_t yacc,int16_t zacc,int16_t xgyro,int16_t ygyro,int16_t zgyro,int16_t xmag,int16_t ymag,int16_t zmag,const float *acc_cov,const float *gyro_cov,const float *mag_cov,int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_COVARIANCE_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int16_t(buf, 112, xacc);
    _mav_put_int16_t(buf, 114, yacc);
    _mav_put_int16_t(buf, 116, zacc);
    _mav_put_int16_t(buf, 118, xgyro);
    _mav_put_int16_t(buf, 120, ygyro);
    _mav_put_int16_t(buf, 122, zgyro);
    _mav_put_int16_t(buf, 124, xmag);
    _mav_put_int16_t(buf, 126, ymag);
    _mav_put_int16_t(buf, 128, zmag);
    _mav_put_int16_t(buf, 130, temperature);
    _mav_put_float_array(buf, 4, acc_cov, 9);
    _mav_put_float_array(buf, 40, gyro_cov, 9);
    _mav_put_float_array(buf, 76, mag_cov, 9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN);
#else
    mavlink_imu_covariance_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;
    packet.temperature = temperature;
    mav_array_memcpy(packet.acc_cov, acc_cov, sizeof(float)*9);
    mav_array_memcpy(packet.gyro_cov, gyro_cov, sizeof(float)*9);
    mav_array_memcpy(packet.mag_cov, mag_cov, sizeof(float)*9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IMU_COVARIANCE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_CRC);
}

/**
 * @brief Encode a imu_covariance struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param imu_covariance C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_covariance_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_imu_covariance_t* imu_covariance)
{
    return mavlink_msg_imu_covariance_pack(system_id, component_id, msg, imu_covariance->time_boot_ms, imu_covariance->xacc, imu_covariance->yacc, imu_covariance->zacc, imu_covariance->xgyro, imu_covariance->ygyro, imu_covariance->zgyro, imu_covariance->xmag, imu_covariance->ymag, imu_covariance->zmag, imu_covariance->acc_cov, imu_covariance->gyro_cov, imu_covariance->mag_cov, imu_covariance->temperature);
}

/**
 * @brief Encode a imu_covariance struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param imu_covariance C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_imu_covariance_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_imu_covariance_t* imu_covariance)
{
    return mavlink_msg_imu_covariance_pack_chan(system_id, component_id, chan, msg, imu_covariance->time_boot_ms, imu_covariance->xacc, imu_covariance->yacc, imu_covariance->zacc, imu_covariance->xgyro, imu_covariance->ygyro, imu_covariance->zgyro, imu_covariance->xmag, imu_covariance->ymag, imu_covariance->zmag, imu_covariance->acc_cov, imu_covariance->gyro_cov, imu_covariance->mag_cov, imu_covariance->temperature);
}

/**
 * @brief Send a imu_covariance message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param xacc [mG] X acceleration
 * @param yacc [mG] Y acceleration
 * @param zacc [mG] Z acceleration
 * @param xgyro [mrad/s] Angular speed around X axis
 * @param ygyro [mrad/s] Angular speed around Y axis
 * @param zgyro [mrad/s] Angular speed around Z axis
 * @param xmag [mgauss] X Magnetic field
 * @param ymag [mgauss] Y Magnetic field
 * @param zmag [mgauss] Z Magnetic field
 * @param acc_cov [-] Covariance matrix for accelerometer
 * @param gyro_cov [-] Covariance matrix for gyroscope
 * @param mag_cov [-] Covariance matrix for magnetometer
 * @param temperature [cdegC] Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_imu_covariance_send(mavlink_channel_t chan, uint32_t time_boot_ms, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag, const float *acc_cov, const float *gyro_cov, const float *mag_cov, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IMU_COVARIANCE_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int16_t(buf, 112, xacc);
    _mav_put_int16_t(buf, 114, yacc);
    _mav_put_int16_t(buf, 116, zacc);
    _mav_put_int16_t(buf, 118, xgyro);
    _mav_put_int16_t(buf, 120, ygyro);
    _mav_put_int16_t(buf, 122, zgyro);
    _mav_put_int16_t(buf, 124, xmag);
    _mav_put_int16_t(buf, 126, ymag);
    _mav_put_int16_t(buf, 128, zmag);
    _mav_put_int16_t(buf, 130, temperature);
    _mav_put_float_array(buf, 4, acc_cov, 9);
    _mav_put_float_array(buf, 40, gyro_cov, 9);
    _mav_put_float_array(buf, 76, mag_cov, 9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_COVARIANCE, buf, MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_CRC);
#else
    mavlink_imu_covariance_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;
    packet.temperature = temperature;
    mav_array_memcpy(packet.acc_cov, acc_cov, sizeof(float)*9);
    mav_array_memcpy(packet.gyro_cov, gyro_cov, sizeof(float)*9);
    mav_array_memcpy(packet.mag_cov, mag_cov, sizeof(float)*9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_COVARIANCE, (const char *)&packet, MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_CRC);
#endif
}

/**
 * @brief Send a imu_covariance message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_imu_covariance_send_struct(mavlink_channel_t chan, const mavlink_imu_covariance_t* imu_covariance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_imu_covariance_send(chan, imu_covariance->time_boot_ms, imu_covariance->xacc, imu_covariance->yacc, imu_covariance->zacc, imu_covariance->xgyro, imu_covariance->ygyro, imu_covariance->zgyro, imu_covariance->xmag, imu_covariance->ymag, imu_covariance->zmag, imu_covariance->acc_cov, imu_covariance->gyro_cov, imu_covariance->mag_cov, imu_covariance->temperature);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_COVARIANCE, (const char *)imu_covariance, MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_CRC);
#endif
}

#if MAVLINK_MSG_ID_IMU_COVARIANCE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_imu_covariance_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag, const float *acc_cov, const float *gyro_cov, const float *mag_cov, int16_t temperature)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_int16_t(buf, 112, xacc);
    _mav_put_int16_t(buf, 114, yacc);
    _mav_put_int16_t(buf, 116, zacc);
    _mav_put_int16_t(buf, 118, xgyro);
    _mav_put_int16_t(buf, 120, ygyro);
    _mav_put_int16_t(buf, 122, zgyro);
    _mav_put_int16_t(buf, 124, xmag);
    _mav_put_int16_t(buf, 126, ymag);
    _mav_put_int16_t(buf, 128, zmag);
    _mav_put_int16_t(buf, 130, temperature);
    _mav_put_float_array(buf, 4, acc_cov, 9);
    _mav_put_float_array(buf, 40, gyro_cov, 9);
    _mav_put_float_array(buf, 76, mag_cov, 9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_COVARIANCE, buf, MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_CRC);
#else
    mavlink_imu_covariance_t *packet = (mavlink_imu_covariance_t *)msgbuf;
    packet->time_boot_ms = time_boot_ms;
    packet->xacc = xacc;
    packet->yacc = yacc;
    packet->zacc = zacc;
    packet->xgyro = xgyro;
    packet->ygyro = ygyro;
    packet->zgyro = zgyro;
    packet->xmag = xmag;
    packet->ymag = ymag;
    packet->zmag = zmag;
    packet->temperature = temperature;
    mav_array_memcpy(packet->acc_cov, acc_cov, sizeof(float)*9);
    mav_array_memcpy(packet->gyro_cov, gyro_cov, sizeof(float)*9);
    mav_array_memcpy(packet->mag_cov, mag_cov, sizeof(float)*9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IMU_COVARIANCE, (const char *)packet, MAVLINK_MSG_ID_IMU_COVARIANCE_MIN_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN, MAVLINK_MSG_ID_IMU_COVARIANCE_CRC);
#endif
}
#endif

#endif

// MESSAGE IMU_COVARIANCE UNPACKING


/**
 * @brief Get field time_boot_ms from imu_covariance message
 *
 * @return [ms] Timestamp (time since system boot).
 */
static inline uint32_t mavlink_msg_imu_covariance_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field xacc from imu_covariance message
 *
 * @return [mG] X acceleration
 */
static inline int16_t mavlink_msg_imu_covariance_get_xacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  112);
}

/**
 * @brief Get field yacc from imu_covariance message
 *
 * @return [mG] Y acceleration
 */
static inline int16_t mavlink_msg_imu_covariance_get_yacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  114);
}

/**
 * @brief Get field zacc from imu_covariance message
 *
 * @return [mG] Z acceleration
 */
static inline int16_t mavlink_msg_imu_covariance_get_zacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  116);
}

/**
 * @brief Get field xgyro from imu_covariance message
 *
 * @return [mrad/s] Angular speed around X axis
 */
static inline int16_t mavlink_msg_imu_covariance_get_xgyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  118);
}

/**
 * @brief Get field ygyro from imu_covariance message
 *
 * @return [mrad/s] Angular speed around Y axis
 */
static inline int16_t mavlink_msg_imu_covariance_get_ygyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  120);
}

/**
 * @brief Get field zgyro from imu_covariance message
 *
 * @return [mrad/s] Angular speed around Z axis
 */
static inline int16_t mavlink_msg_imu_covariance_get_zgyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  122);
}

/**
 * @brief Get field xmag from imu_covariance message
 *
 * @return [mgauss] X Magnetic field
 */
static inline int16_t mavlink_msg_imu_covariance_get_xmag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  124);
}

/**
 * @brief Get field ymag from imu_covariance message
 *
 * @return [mgauss] Y Magnetic field
 */
static inline int16_t mavlink_msg_imu_covariance_get_ymag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  126);
}

/**
 * @brief Get field zmag from imu_covariance message
 *
 * @return [mgauss] Z Magnetic field
 */
static inline int16_t mavlink_msg_imu_covariance_get_zmag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  128);
}

/**
 * @brief Get field acc_cov from imu_covariance message
 *
 * @return [-] Covariance matrix for accelerometer
 */
static inline uint16_t mavlink_msg_imu_covariance_get_acc_cov(const mavlink_message_t* msg, float *acc_cov)
{
    return _MAV_RETURN_float_array(msg, acc_cov, 9,  4);
}

/**
 * @brief Get field gyro_cov from imu_covariance message
 *
 * @return [-] Covariance matrix for gyroscope
 */
static inline uint16_t mavlink_msg_imu_covariance_get_gyro_cov(const mavlink_message_t* msg, float *gyro_cov)
{
    return _MAV_RETURN_float_array(msg, gyro_cov, 9,  40);
}

/**
 * @brief Get field mag_cov from imu_covariance message
 *
 * @return [-] Covariance matrix for magnetometer
 */
static inline uint16_t mavlink_msg_imu_covariance_get_mag_cov(const mavlink_message_t* msg, float *mag_cov)
{
    return _MAV_RETURN_float_array(msg, mag_cov, 9,  76);
}

/**
 * @brief Get field temperature from imu_covariance message
 *
 * @return [cdegC] Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).
 */
static inline int16_t mavlink_msg_imu_covariance_get_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  130);
}

/**
 * @brief Decode a imu_covariance message into a struct
 *
 * @param msg The message to decode
 * @param imu_covariance C-struct to decode the message contents into
 */
static inline void mavlink_msg_imu_covariance_decode(const mavlink_message_t* msg, mavlink_imu_covariance_t* imu_covariance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    imu_covariance->time_boot_ms = mavlink_msg_imu_covariance_get_time_boot_ms(msg);
    mavlink_msg_imu_covariance_get_acc_cov(msg, imu_covariance->acc_cov);
    mavlink_msg_imu_covariance_get_gyro_cov(msg, imu_covariance->gyro_cov);
    mavlink_msg_imu_covariance_get_mag_cov(msg, imu_covariance->mag_cov);
    imu_covariance->xacc = mavlink_msg_imu_covariance_get_xacc(msg);
    imu_covariance->yacc = mavlink_msg_imu_covariance_get_yacc(msg);
    imu_covariance->zacc = mavlink_msg_imu_covariance_get_zacc(msg);
    imu_covariance->xgyro = mavlink_msg_imu_covariance_get_xgyro(msg);
    imu_covariance->ygyro = mavlink_msg_imu_covariance_get_ygyro(msg);
    imu_covariance->zgyro = mavlink_msg_imu_covariance_get_zgyro(msg);
    imu_covariance->xmag = mavlink_msg_imu_covariance_get_xmag(msg);
    imu_covariance->ymag = mavlink_msg_imu_covariance_get_ymag(msg);
    imu_covariance->zmag = mavlink_msg_imu_covariance_get_zmag(msg);
    imu_covariance->temperature = mavlink_msg_imu_covariance_get_temperature(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_IMU_COVARIANCE_LEN? msg->len : MAVLINK_MSG_ID_IMU_COVARIANCE_LEN;
        memset(imu_covariance, 0, MAVLINK_MSG_ID_IMU_COVARIANCE_LEN);
    memcpy(imu_covariance, _MAV_PAYLOAD(msg), len);
#endif
}
