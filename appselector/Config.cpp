/* === This file is part of calamares-modules-slimbook - <https://github.com/Slimbook-Team> ===
 *
 *   SPDX-FileCopyrightText: 2024 Slimbook <dev@slimbook.es>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
  */

#include "Config.hpp"

#include <slimbook.h>

#include <GlobalStorage.h>
#include <JobQueue.h>
#include <QMap>

#include <QDebug>

Config::Config(QObject* parent) : QObject(parent)
{
    m_slimbook_model = slb_info_get_model();
    m_slimbook_product = slb_info_product_name();
    m_slimbook_family = slb_info_get_family_name();


    QMap<QString,QString> pretty = {{"unknown","Unknown"},
        {"prox","ProX"},
        {"executive","Executive"},
        {"titan","Titan"},
        {"hero","Hero"},
        {"hero-s","Hero-S"},
        {"essential","Essential"},
        {"elemental","Elemental"},
        {"excalibur","Excalibur"},
        {"one","One"},
        {"zero","Zero"}
    };

    m_slimbook_name = pretty[m_slimbook_family];

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
            QMap<QString, QVariant>::const_iterator core = app.find("core");
            QMap<QString, QVariant>::const_iterator target = app.find("target");
            
            if (name!=app.end()) {

                QList<QVariant> targets = target.value().toList();
                bool found = false;

                for (int n=0;n<targets.count();n++) {
                    QString value = targets[n].toString();

                    if (value == m_slimbook_family || value == "all") {
                        found = true;
                        break;
                    }
                }

                if (found) {

                    QString desc = (description!=app.end()) ? description.value().toString() : name.value().toString();

                    bool iscore = (core!=app.end()) ? core.value().toBool() : false;
                    bool ischeck = m_slimbook_model > 0;

                    //qWarning()<<"SLIMBOOK APP:"<<name.value().toString();
                    m_appsModel.append(new App(
                        name.value().toString(),
                        desc,
                        iscore,
                        ischeck
                        ));
                }
            }
            
            j++;
        }
    }
    
    //qDebug()<<m_translations;
}
