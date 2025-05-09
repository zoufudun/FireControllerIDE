#include "dimoduleconfigdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>
#include <QSplitter>

DIModuleConfigDialog::DIModuleConfigDialog(DIModule *module, QWidget *parent)
    : QDialog(parent), m_module(module), m_currentChannelIndex(0)
{
    setWindowTitle("DI模块配置");
    setMinimumSize(600, 400);
    
    setupUI();
    updateBitTable(m_currentChannelIndex);
}

DIModuleConfigDialog::~DIModuleConfigDialog()
{
}

void DIModuleConfigDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // 通道数量选择
    QHBoxLayout *channelCountLayout = new QHBoxLayout();
    QLabel *channelCountLabel = new QLabel("通道数量:", this);
    m_channelCountCombo = new QComboBox(this);
    m_channelCountCombo->addItem("8通道", 8);
    m_channelCountCombo->addItem("16通道", 16);
    m_channelCountCombo->addItem("32通道", 32);
    
    // 设置当前选中的通道数量
    int currentIndex = 0;
    switch (m_module->getChannelCount()) {
        case 8: currentIndex = 0; break;
        case 16: currentIndex = 1; break;
        case 32: currentIndex = 2; break;
    }
    m_channelCountCombo->setCurrentIndex(currentIndex);
    
    channelCountLayout->addWidget(channelCountLabel);
    channelCountLayout->addWidget(m_channelCountCombo);
    
    // 添加通道选择下拉框
    QLabel *channelSelectLabel = new QLabel("选择通道:", this);
    m_channelSelectCombo = new QComboBox(this);
    
    // 根据当前通道数量填充通道选择下拉框
    for (int i = 0; i < m_module->getChannelCount(); ++i) {
        m_channelSelectCombo->addItem(QString("通道 %1").arg(i), i);
    }
    
    channelCountLayout->addSpacing(20);
    channelCountLayout->addWidget(channelSelectLabel);
    channelCountLayout->addWidget(m_channelSelectCombo);
    channelCountLayout->addStretch();
    
    mainLayout->addLayout(channelCountLayout);
    
    // 位变量表格
    m_bitTable = new QTableWidget(8, 3, this);
    m_bitTable->setHorizontalHeaderLabels(QStringList() << "位" << "变量名" << "描述");
    m_bitTable->verticalHeader()->setVisible(false);
    
    // 设置表格列可以拖动调整大小
    m_bitTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    m_bitTable->horizontalHeader()->setStretchLastSection(true);
    
    // 设置默认列宽
    m_bitTable->setColumnWidth(0, 50);  // 位列宽度较小
    m_bitTable->setColumnWidth(1, 200); // 变量名列宽度适中
    
    mainLayout->addWidget(m_bitTable);
    
    // 按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_saveButton = new QPushButton("保存", this);
    m_cancelButton = new QPushButton("取消", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // 连接信号
    connect(m_channelCountCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DIModuleConfigDialog::onChannelCountChanged);
    connect(m_channelSelectCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DIModuleConfigDialog::onChannelSelectionChanged);
    connect(m_saveButton, &QPushButton::clicked, this, &DIModuleConfigDialog::saveConfiguration);
    connect(m_cancelButton, &QPushButton::clicked, this, &DIModuleConfigDialog::reject);
    connect(m_bitTable, &QTableWidget::cellChanged, this, &DIModuleConfigDialog::onBitVariableChanged);
}

void DIModuleConfigDialog::updateBitTable(int channelIndex)
{
    if (channelIndex < 0 || channelIndex >= m_module->getChannelCount()) {
        return;
    }
    
    // 断开信号连接，避免触发onBitVariableChanged
    disconnect(m_bitTable, &QTableWidget::cellChanged, this, nullptr);
    
    DIChannel *channel = m_module->getChannel(channelIndex);
    if (!channel) {
        return;
    }
    
    // 更新表格数据
    for (int j = 0; j < 8; ++j) {
        // 位编号
        QTableWidgetItem *bitItem = m_bitTable->item(j, 0);
        if (!bitItem) {
            bitItem = new QTableWidgetItem(QString::number(j));
            bitItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            m_bitTable->setItem(j, 0, bitItem);
        }
        
        // 变量名
        QTableWidgetItem *nameItem = m_bitTable->item(j, 1);
        if (!nameItem) {
            nameItem = new QTableWidgetItem(channel->bits[j].name);
            m_bitTable->setItem(j, 1, nameItem);
        } else {
            nameItem->setText(channel->bits[j].name);
        }
        
        // 描述
        QTableWidgetItem *descItem = m_bitTable->item(j, 2);
        if (!descItem) {
            descItem = new QTableWidgetItem(channel->bits[j].description);
            m_bitTable->setItem(j, 2, descItem);
        } else {
            descItem->setText(channel->bits[j].description);
        }
    }
    
    // 重新连接信号
    connect(m_bitTable, &QTableWidget::cellChanged, this, &DIModuleConfigDialog::onBitVariableChanged);
}

void DIModuleConfigDialog::onChannelCountChanged(int index)
{
    // 获取新的通道数量
    int newChannelCount = m_channelCountCombo->itemData(index).toInt();
    
    // 更新模块的通道数量
    m_module->setChannelCount(newChannelCount);
    
    // 更新通道选择下拉框
    m_channelSelectCombo->clear();
    for (int i = 0; i < newChannelCount; ++i) {
        m_channelSelectCombo->addItem(QString("通道 %1").arg(i), i);
    }
    
    // 重置当前通道索引
    m_currentChannelIndex = 0;
    m_channelSelectCombo->setCurrentIndex(0);
    
    // 更新位变量表格
    updateBitTable(m_currentChannelIndex);
}

void DIModuleConfigDialog::onChannelSelectionChanged(int index)
{
    m_currentChannelIndex = index;
    updateBitTable(m_currentChannelIndex);
}

void DIModuleConfigDialog::onBitVariableChanged(int row, int column)
{
    // 只处理变量名和描述列
    if (column != 1 && column != 2) {
        return;
    }
    
    // 获取变量名和描述
    QString name = m_bitTable->item(row, 1) ? m_bitTable->item(row, 1)->text() : "";
    QString description = m_bitTable->item(row, 2) ? m_bitTable->item(row, 2)->text() : "";
    
    // 更新模块数据
    DIBitVariable variable;
    variable.name = name;
    variable.description = description;
    variable.isGlobal = true;  // 默认设置为全局变量
    
    m_module->setBitVariable(m_currentChannelIndex, row, variable);
}

void DIModuleConfigDialog::saveConfiguration()
{
    // 这里可以添加保存配置的逻辑
    // 例如，保存到文件或数据库
    
    QMessageBox::information(this, "保存配置", "DI模块配置已保存");
    accept();
}