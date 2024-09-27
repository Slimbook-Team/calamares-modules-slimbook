
#include "Config.hpp"

#include <GlobalStorage.h>
#include <JobQueue.h>

#include <QDebug>

Config::Config(QObject* parent) : QObject(parent)
{

    
}

void Config::store()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QList<QVariant> apps;
    
    QList<QObject* >::const_iterator i = m_appsModel.begin();
    
    while(i!=m_appsModel.end()) {
        
        App* app = static_cast<App*>(*i);
        
        if (app->m_checked) {
            apps.append(app->m_name);
        }
        
        i++;
    }
    
    gs->insert( "slimbook_extra_apps", apps );
    

}


void Config::setConfigurationMap(const QVariantMap& configurationMap)
{
    
    QMap<QString, QVariant>::const_iterator i = configurationMap.find("apps");
    
    if (i!=configurationMap.end()) {
        QVariantList apps = i.value().toList();
        
        QList<QVariant>::const_iterator j = apps.begin();
        
        while (j!=apps.end()) {
            
            QMap<QString,QVariant> app = (*j).toMap();
            
            QMap<QString, QVariant>::const_iterator name = app.find("name");
            QMap<QString, QVariant>::const_iterator description = app.find("description");
            QMap<QString, QVariant>::const_iterator checked = app.find("checked");
            
            if (name!=app.end() and display!=app.end() and icon!=app.end()) {
                QString desc = (description!=app.end()) ? description.value().toString() : QString();
                bool chk = (checked!=app.end()) ? checked.value().toBool() : false;
                
                m_appsModel.append(new App(
                    name.value().toString(),
                    desc,
                    chk
                    ));
            }
            
            j++;
        }
    }
    
    //qDebug()<<m_translations;
}
