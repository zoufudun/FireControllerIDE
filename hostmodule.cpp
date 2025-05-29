#include "hostmodule.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include <QRegularExpression>

// Remove the class declaration - it should only be in the header file
// class HostModule : public QObject { ... }  <- DELETE THIS

HostModule::HostModule(QObject *parent)
    : QObject(parent)
{
    // Constructor implementation
}

HostModule::~HostModule()
{
}

HostConfiguration HostModule::getConfiguration() const
{
    return m_configuration;
}

void HostModule::setConfiguration(const HostConfiguration &config)
{
    m_configuration = config;
}

bool HostModule::isValidIPAddress(const QString &ip) const
{
    QHostAddress address(ip);
    return !address.isNull() && address.protocol() == QAbstractSocket::IPv4Protocol;
}

bool HostModule::isValidPort(int port) const
{
    return port >= 1 && port <= 65535;
}

void HostModule::saveConfiguration(const QString &filePath)
{
    QJsonObject rootObj;
    
    // 保存主机配置
    rootObj["hostName"] = m_configuration.hostName;
    rootObj["ipAddress"] = m_configuration.ipAddress;
    rootObj["port"] = m_configuration.port;
    rootObj["protocol"] = (m_configuration.protocol == CommunicationProtocol::TCP) ? "TCP" : "UDP";
    rootObj["subnetMask"] = m_configuration.subnetMask;
    rootObj["gateway"] = m_configuration.gateway;
    rootObj["description"] = m_configuration.description;
    rootObj["dhcpEnabled"] = m_configuration.dhcpEnabled;
    
    // 保存到文件
    QJsonDocument doc(rootObj);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void HostModule::loadConfiguration(const QString &filePath)
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
    
    // 读取主机配置
    if (rootObj.contains("hostName")) {
        m_configuration.hostName = rootObj["hostName"].toString();
    }
    if (rootObj.contains("ipAddress")) {
        m_configuration.ipAddress = rootObj["ipAddress"].toString();
    }
    if (rootObj.contains("port")) {
        m_configuration.port = rootObj["port"].toInt();
    }
    if (rootObj.contains("protocol")) {
        QString protocol = rootObj["protocol"].toString();
        m_configuration.protocol = (protocol == "TCP") ? CommunicationProtocol::TCP : CommunicationProtocol::UDP;
    }
    if (rootObj.contains("subnetMask")) {
        m_configuration.subnetMask = rootObj["subnetMask"].toString();
    }
    if (rootObj.contains("gateway")) {
        m_configuration.gateway = rootObj["gateway"].toString();
    }
    if (rootObj.contains("description")) {
        m_configuration.description = rootObj["description"].toString();
    }
    if (rootObj.contains("dhcpEnabled")) {
        m_configuration.dhcpEnabled = rootObj["dhcpEnabled"].toBool();
    }
}

bool HostModule::testConnection() const
{
    // 这里可以实现实际的网络连接测试
    // 暂时返回true作为示例
    return isValidIPAddress(m_configuration.ipAddress) && isValidPort(m_configuration.port);
}


void HostModule::setComponentId(const QString &id) 
{ 
    m_componentId = id; 
}

QString HostModule::getComponentId() const 
{ 
    return m_componentId; 
}

void HostModule::saveConfiguration()
{
    // Implementation here
}

void HostModule::loadConfiguration()
{
    // Implementation here
}
    
