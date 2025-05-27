#ifndef HOSTMODULE_H
#define HOSTMODULE_H

#include <QObject>
#include <QString>
 #include <QHostAddress>

// 定义通信协议枚举
enum class CommunicationProtocol {
    TCP,
    UDP
};

// 定义主机配置结构
struct HostConfiguration {
    QString hostName;                    // 主机名称
    QString ipAddress;                   // IP地址
    int port;                           // 端口号
    CommunicationProtocol protocol;     // 通信协议
    QString subnetMask;                 // 子网掩码
    QString gateway;                    // 网关
    QString description;                // 描述
    bool dhcpEnabled;                   // 是否启用DHCP
    
    HostConfiguration() {
        hostName = "Controller";
        ipAddress = "192.168.1.100";
        port = 502;
        protocol = CommunicationProtocol::TCP;
        subnetMask = "255.255.255.0";
        gateway = "192.168.1.1";
        description = "控制器主机";
        dhcpEnabled = false;
    }
};

// 主机模块类
class HostModule : public QObject
{
    Q_OBJECT
    
public:
    explicit HostModule(QObject *parent = nullptr);
    ~HostModule();
    
    // 获取和设置主机配置
    HostConfiguration getConfiguration() const;
    void setConfiguration(const HostConfiguration &config);
    
    // 验证IP地址格式
    bool isValidIPAddress(const QString &ip) const;
    
    // 验证端口号
    bool isValidPort(int port) const;
    
    // 保存和加载配置
    void saveConfiguration(const QString &filePath);
    void loadConfiguration(const QString &filePath);
    
    // 测试网络连接
    bool testConnection() const;
    
private:
    HostConfiguration m_configuration;
};

#endif // HOSTMODULE_H
