#ifndef _PROTOBUF_HPP_
#define _PROTOBUF_HPP_

#include <Arduino.h>

#include <pb_encode.h>
#include <pb_decode.h>

#include <orientation_msg.pb.h>

#define MAX_MESSAGE_SIZE 64

namespace RobotTweezers
{
    class Protobuf
    {
    private:
        static bool UartWrite(HardwareSerial *uart, const pb_msgdesc_t *fields, const void *data_struct);

        static bool UartRead(HardwareSerial *uart, const pb_msgdesc_t *fields, void *data_struct);

    public:
        static bool UartWrite(HardwareSerial *uart, const OrientationMsg *orientation_msg);

        static bool UartRead(HardwareSerial *uart, OrientationMsg *orientation_msg);
    };
}

#endif // _PROTOBUF_HPP_