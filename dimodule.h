#ifndef DIMODULE_H
#define DIMODULE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>

// 定义DI模块的位变量结构
struct DIBitVariable {
    QString name;       // 变量名称
    QString description; // 变量描述
    bool isGlobal;      // 是否为全局变量
};

// 定义DI模块的通道结构
struct DIChannel {
    int channelNumber;  // 通道编号
    QVector<DIBitVariable> bits; // 8位变量
    
    DIChannel() {
        // 初始化8位变量
        bits.resize(8);
    }
};

// DI模块类
class DIModule : public QObject
{
    Q_OBJECT
    
public:
    explicit DIModule(QObject *parent = nullptr);
    ~DIModule();
    
    // 设置通道数量（8、16或32）
    void setChannelCount(int count);
    int getChannelCount() const;
    
    // 获取指定通道
    DIChannel* getChannel(int channelNumber);
    
    // 设置位变量
    void setBitVariable(int channelNumber, int bitNumber, const DIBitVariable &variable);
    DIBitVariable getBitVariable(int channelNumber, int bitNumber) const;
    
    // 保存和加载配置
    void saveConfiguration(const QString &filePath);
    void loadConfiguration(const QString &filePath);
    
private:
    int m_channelCount;  // 通道数量
    QVector<DIChannel> m_channels; // 通道列表
};

#endif // DIMODULE_H