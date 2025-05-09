#ifndef DOMODULE_H
#define DOMODULE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>

// 定义DO模块的位变量结构
struct DOBitVariable {
    QString name;       // 变量名称
    QString description; // 变量描述
    bool isGlobal;      // 是否为全局变量
    int value;          // 位的值，0或1
    
    DOBitVariable() : isGlobal(true), value(0) {}  // 默认构造函数，初始化值为0
};

// 定义DO模块的通道结构
struct DOChannel {
    int channelNumber;  // 通道编号
    QVector<DOBitVariable> bits; // 8位变量
    
    DOChannel() {
        // 初始化8位变量
        bits.resize(8);
    }
};

// DO模块类
class DOModule : public QObject
{
    Q_OBJECT
    
public:
    explicit DOModule(QObject *parent = nullptr);
    ~DOModule();
    
    // 设置通道数量（8、16或32）
    void setChannelCount(int count);
    int getChannelCount() const;
    
    // 获取指定通道
    DOChannel* getChannel(int channelNumber);
    
    // 设置位变量
    void setBitVariable(int channelNumber, int bitNumber, const DOBitVariable &variable);
    DOBitVariable getBitVariable(int channelNumber, int bitNumber) const;
    
    // 保存和加载配置
    void saveConfiguration(const QString &filePath);
    void loadConfiguration(const QString &filePath);
    
private:
    int m_channelCount;  // 通道数量
    QVector<DOChannel> m_channels; // 通道列表
};

#endif // DOMODULE_H