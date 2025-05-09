#include "dimodule.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

DIModule::DIModule(QObject *parent)
    : QObject(parent), m_channelCount(8)
{
    // 默认初始化为8个通道
    m_channels.resize(m_channelCount);
    for (int i = 0; i < m_channelCount; ++i) {
        m_channels[i].channelNumber = i;
    }
}

DIModule::~DIModule()
{
}

void DIModule::setChannelCount(int count)
{
    // 只允许8、16或32个通道
    if (count != 8 && count != 16 && count != 32) {
        return;
    }
    
    m_channelCount = count;
    
    // 调整通道数量
    m_channels.resize(m_channelCount);
    
    // 确保每个通道都有正确的编号
    for (int i = 0; i < m_channelCount; ++i) {
        m_channels[i].channelNumber = i;
    }
}

int DIModule::getChannelCount() const
{
    return m_channelCount;
}

DIChannel* DIModule::getChannel(int channelNumber)
{
    if (channelNumber >= 0 && channelNumber < m_channelCount) {
        return &m_channels[channelNumber];
    }
    return nullptr;
}

void DIModule::setBitVariable(int channelNumber, int bitNumber, const DIBitVariable &variable)
{
    if (channelNumber >= 0 && channelNumber < m_channelCount && 
        bitNumber >= 0 && bitNumber < 8) {
        m_channels[channelNumber].bits[bitNumber] = variable;
    }
}

DIBitVariable DIModule::getBitVariable(int channelNumber, int bitNumber) const
{
    if (channelNumber >= 0 && channelNumber < m_channelCount && 
        bitNumber >= 0 && bitNumber < 8) {
        return m_channels[channelNumber].bits[bitNumber];
    }
    return DIBitVariable();
}

void DIModule::saveConfiguration(const QString &filePath)
{
    QJsonObject rootObj;
    
    // 保存通道数量
    rootObj["channelCount"] = m_channelCount;
    
    // 保存通道配置
    QJsonArray channelsArray;
    for (int i = 0; i < m_channelCount; ++i) {
        QJsonObject channelObj;
        channelObj["channelNumber"] = m_channels[i].channelNumber;
        
        // 保存位变量
        QJsonArray bitsArray;
        for (int j = 0; j < 8; ++j) {
            QJsonObject bitObj;
            bitObj["name"] = m_channels[i].bits[j].name;
            bitObj["description"] = m_channels[i].bits[j].description;
            bitObj["isGlobal"] = m_channels[i].bits[j].isGlobal;
            bitObj["value"] = m_channels[i].bits[j].value;  // 保存位值
            bitsArray.append(bitObj);
        }
        
        channelObj["bits"] = bitsArray;
        channelsArray.append(channelObj);
    }
    
    rootObj["channels"] = channelsArray;
    
    // 保存到文件
    QJsonDocument doc(rootObj);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void DIModule::loadConfiguration(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        return;
    }
    
    QJsonObject rootObj = doc.object();
    
    // 读取通道数量
    if (rootObj.contains("channelCount")) {
        setChannelCount(rootObj["channelCount"].toInt());
    }
    
    // 读取通道配置
    if (rootObj.contains("channels") && rootObj["channels"].isArray()) {
        QJsonArray channelsArray = rootObj["channels"].toArray();
        
        for (int i = 0; i < channelsArray.size() && i < m_channelCount; ++i) {
            QJsonObject channelObj = channelsArray[i].toObject();
            int channelNumber = channelObj["channelNumber"].toInt();
            
            // 读取位变量
            if (channelObj.contains("bits") && channelObj["bits"].isArray()) {
                QJsonArray bitsArray = channelObj["bits"].toArray();
                
                for (int j = 0; j < bitsArray.size() && j < 8; ++j) {
                    QJsonObject bitObj = bitsArray[j].toObject();
                    
                    DIBitVariable variable;
                    variable.name = bitObj["name"].toString();
                    variable.description = bitObj["description"].toString();
                    variable.isGlobal = bitObj["isGlobal"].toBool();
                    variable.value = bitObj.contains("value") ? bitObj["value"].toInt() : 0;  // 读取位值，如果不存在则默认为0
                    
                    setBitVariable(channelNumber, j, variable);
                }
            }
        }
    }
}