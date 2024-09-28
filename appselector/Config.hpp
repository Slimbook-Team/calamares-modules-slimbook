
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QString>
#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>

class App: public QObject
{
    Q_OBJECT
    
    Q_PROPERTY( QString name MEMBER m_name READ name CONSTANT)
    Q_PROPERTY( QString description MEMBER m_description READ description CONSTANT)
    Q_PROPERTY (bool checked MEMBER m_checked NOTIFY checkedChanged)
    
    public:
    
    QString m_name;
    QString m_description;
    bool m_checked;
    
    QString name () const
    {
        return m_name;
    }
    
    QString description () const
    {
        return m_description;
    }
    
    App(QString name, QString description, bool checked) :
        m_name(name),
        m_description(description),
        m_checked(checked)
    {
    }
    
    Q_SIGNALS:
        
    void checkedChanged();
    
    private:
    

};

class Config : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QList<QObject *> appsModel MEMBER m_appsModel NOTIFY appsModelChanged)
    
    public:
    
    Config(QObject* parent = nullptr);
    
    void setConfigurationMap(const QVariantMap& configurationMap);
    
    void store();
    
    
    QList<QObject *> m_appsModel;
        
    Q_SIGNALS:
    
    void appsModelChanged();
    
    private:
    
    
};

#endif
