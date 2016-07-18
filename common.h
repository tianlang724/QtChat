#ifndef COMMON_H
#define COMMON_H

#define UDP_LISTEN_PORT 6666

#define MSG_TYPE_DATA 0x00
#define MSG_TYPE_ONLINE 0x01
#define MSG_TYPE_OFFLINE 0x02


struct SMessage
{
    char type;
    int length;
    //length 指的是数据部分长度
    char *data;
};

#endif // COMMON_H
