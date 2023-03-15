#include "udpincomingprocessor.h"
#include "c6657udp.h"
#include <qdebug.h>
#include <IoLoger.h>
UdpIncomingProcessor::UdpIncomingProcessor(IIoLoger* l)
    :current_data_id(0x3f4e2d1a5c)
    ,received_data_bytes(0)
    ,current_img_id(0x3f4e2d1a5c)
    ,loger(l)
{

}

/************************
//UDP用户头结构体
*************************/
struct C6657UdpIOHeader
{
    /** 标识符和数据类型
    *	0x00465A48	交互命令。上下位机可互发
    *	0x01465A48	图像数据。下位机发给上位机。
    *	0x02465A48	处理结果。下位机发给上位机。
    *	0x03......  DSP 固件。
    *   0x04......  DSP 内存数据
    **/
    unsigned int dataType;
    unsigned int dataID;

    /** dataID 对应的总的数据长度（字节），
     * 不含任何头部信息，例如处理结果 4k 大小，此处即为 4k
     **/
    unsigned int dataTotalLen;

    /** 当前用户数据首字节在整个 DataID 的偏移地址.
     * 例如处理结果 4k 大小，分 4 个 1k 传输，第一次传
     * 输 dataIdx 为 0（首包），第二次传输 dataIdx 为 1k，依此
     * 类推，当 dataIdx+dataLen==dataTotalLen 时表示最后一次
     * 传输（尾包）
     **/

    unsigned int dataIdx;

    /** 当前数据包的数据长度（字节）.
     * 不含任何头部信息，例如传输1k 处理结果的包，此处为1k.
     * 当dataLen=0，接收方反馈已经接收到了对应的数据包。
     **/
    unsigned short dataLen;
    /** 可选项,0表示无效*/
    unsigned short CheckSum;
};

long UdpIncomingProcessor::new_frame_arrived(void * _frame, size_t size)
{
    C6657Udp::frame_type* frame=(C6657Udp::frame_type*)_frame;
    C6657UdpIOHeader* header = (C6657UdpIOHeader*)(frame->data());

    //img
    if( header->dataType == 0x01465A48) {

    } else if ( header->dataType == 0x02465A48) { //data result
        if(current_data_id != header->dataID ){ //new data result.
            memset( data, 0, sizeof(data));
            current_data_id=header->dataID;
            received_data_bytes=0;
        }

        if( current_data_id==header->dataID){
            memmove(data + header->dataIdx, frame->data()+20, header->dataLen);
            received_data_bytes += header->dataLen;

            if( header->dataIdx + header->dataLen == header->dataTotalLen ){ //finished the total data message.
                if( received_data_bytes ==header->dataTotalLen ){
                    uint32_t* result_data =data;
                    loger->uint32dump(true, result_data, received_data_bytes / 4);
                    //qDebug()
                    //        << result_data[3] <<"," << result_data[4] <<"," << result_data[5] <<","<<result_data[6]
                    //        << "|" << result_data[16] << "," <<result_data[17] <<"," << result_data[18] << "," << result_data[19]
                    //        << "," << result_data[20] << "," << result_data[21] ;
                } else {
                    qDebug() << "丢帧:收到的长度:" << received_data_bytes <<",应收长度:"<<header->dataTotalLen;
                }
            }
        }
    } else if ( header->dataType == 0x00465A48) { //cmd / response
        qDebug() << "cmd/response";
    } else {
        qDebug() << "unknow";
    }
    return 0;
}
