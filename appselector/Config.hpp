/* === This file is part of calamares-modules-slimbook - <https://github.com/Slimbook-Team> ===
 *
 *   SPDX-FileCopyrightText: 2024 Slimbook <dev@slimbook.es>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
  */

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
    Q_PROPERTY( bool checked MEMBER m_checked NOTIFY checkedChanged)
    Q_PROPERTY( bool core MEMBER m_core READ core CONSTANT)

    public:
    
    QString m_name;
    QString m_description;
    bool m_checked;
    bool m_core;
    
    bool core() const
    {
        return m_core;
    }

    QString name () const
    {
        return m_name;
    }
    
    QString description () const
    {
        return m_description;
    }
    
    App(QString name, QString description, bool core) :
        m_name(name),
        m_description(description),
        m_core(core),
        m_checked(true)
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
    Q_PROPERTY( int model MEMBER m_slimbook_model READ model CONSTANT)
    Q_PROPERTY( QString family MEMBER m_slimbook_family READ family CONSTANT)
    Q_PROPERTY( QString name MEMBER m_slimbook_name READ name CONSTANT)
    Q_PROPERTY( QString product MEMBER m_slimbook_product READ product CONSTANT)
    
    public:
    
    Config(QObject* parent = nullptr);
    
    void setConfigurationMap(const QVariantMap& configurationMap);
    
    void store();

    QString product() const
    {
        return m_slimbook_product;
    }

    QString name() const
    {
       return m_slimbook_name;
    }

    QString family() const
    {
        return m_slimbook_family;
    }

    int model() const
    {
        return m_slimbook_model;
    }
    
    QList<QObject *> m_appsModel;
        
    Q_SIGNALS:
    
    void appsModelChanged();


    private:
    
    QString m_slimbook_product;
    QString m_slimbook_name;
    QString m_slimbook_family;
    int m_slimbook_model;
};

#endif
