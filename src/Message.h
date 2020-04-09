#ifndef NEWS_BLOCK_CHAIN_MESSAGE_H
#define NEWS_BLOCK_CHAIN_MESSAGE_H

#include <string>

template<class T>
class Message {
public:
    /**
     * 状态码
     */
    int code;

    /**
     * 消息
     */
    std::string msg;

    /**
     * 数据
     */
    T *data;

    Message(int code, std::string msg, T *data = nullptr);

    /**
     * 返回成功的消息
     * @param msg x消息
     * @param data 数据
     * @return
     */
    static Message<T> success(std::string msg, T *data = nullptr);

    /**
     * 返回失败的消息
     * @param code 状态码
     * @param msg 消息
     * @return
     */
    static Message fail(int code, std::string msg);
};


template<class T>
Message<T>::Message(int code, std::string msg, T *data) :code(code), msg(msg), data(data){}

template<class T>
Message<T> Message<T>::success(std::string msg, T *data) {
    return Message(200, msg, data);
}

template<class T>
Message<T> Message<T>::fail(int code, std::string msg) {
    return Message(code, msg);
}


#endif //NEWS_BLOCK_CHAIN_MESSAGE_H
