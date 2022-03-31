#include <protobuf.hpp>

bool RobotTweezers::Protobuf::UartWrite(HardwareSerial *uart, const pb_msgdesc_t *fields, const void *data_struct)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    pb_ostream_t ostream;
    bool status = false;
    
    ostream = pb_ostream_from_buffer(buffer, MAX_MESSAGE_SIZE);
    
    if (pb_encode(&ostream, fields, data_struct) == true)
    {
        status = true;
        uart->write(ostream.bytes_written);
        for (size_t i = 0; i < ostream.bytes_written; i++)
        {
            uart->write(buffer[i]);
        }
    }

    return status;
}

bool RobotTweezers::Protobuf::UartRead(HardwareSerial *uart, const pb_msgdesc_t *fields, void *data_struct)
{
    pb_byte_t buffer[MAX_MESSAGE_SIZE];
    pb_istream_t istream;
    size_t size;
    bool status = true;

    if (uart->available() > 0)
    {
        // Read first byte, should indicate message size
        size = uart->read();
        for (size_t i = 0; i < size; i++)
        {
            // Read message into buffer
            buffer[i] = uart->read();
        }

        istream = pb_istream_from_buffer(buffer, size);

        if (pb_decode(&istream, fields, data_struct) == false)
        {
            status = false;
        }
    }
    else
    {
        status = false;
    }

    return status;
}

bool RobotTweezers::Protobuf::UartWrite(HardwareSerial *uart, const OrientationMsg *orientation_msg)
{
    return UartWrite(uart, OrientationMsg_fields, (const void *)orientation_msg);
}

bool RobotTweezers::Protobuf::UartRead(HardwareSerial *uart, OrientationMsg *orientation_msg)
{
    return UartRead(uart, OrientationMsg_fields, orientation_msg);
}