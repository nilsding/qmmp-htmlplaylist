/* qmmp-htmlplaylist -- exports your playlist as a single HTML file
 * Copyright (C) 2020 Georg Gadinger <nilsding@nilsding.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <QSettings>
#include <qmmp/qmmp.h>

#include "template.h"

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::SettingsDialog)
{
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);

    m_ui->setupUi(this);

    m_ui->qcbTheme->clear();
    m_ui->qcbTheme->addItem(tr("Winamp"), Template::Winamp);
    m_ui->qcbTheme->addItem(tr("Unstyled HTML"), Template::UnstyledHTML);

    m_ui->qleTitle->setText(settings.value("htmlplaylist_plugin/title", "Winamp Generated PlayList").toString());
    int theme = settings.value("htmlplaylist_plugin/theme", Template::Winamp).toInt();
    int index = m_ui->qcbTheme->findData(theme);
    m_ui->qcbTheme->setCurrentIndex(index);

    m_ui->qcbIncludeSaveAs->setChecked(settings.value("htmlplaylist_plugin/include_save_as", true).toBool());
    m_ui->qcbShowTrackPosition->setChecked(settings.value("htmlplaylist_plugin/show_track_position", true).toBool());
    m_ui->qcbShowTrackDuration->setChecked(settings.value("htmlplaylist_plugin/show_track_duration", true).toBool());
}

SettingsDialog::~SettingsDialog()
{
    delete m_ui;
}

void SettingsDialog::accept()
{
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);

    if (m_ui->qleTitle->text().isEmpty())
    {
        m_ui->qleTitle->setText("Winamp Generated PlayList");
    }

    settings.setValue("htmlplaylist_plugin/title", m_ui->qleTitle->text());
    settings.setValue("htmlplaylist_plugin/theme", m_ui->qcbTheme->currentData().toInt());
    settings.setValue("htmlplaylist_plugin/include_save_as", m_ui->qcbIncludeSaveAs->isChecked());
    settings.setValue("htmlplaylist_plugin/show_track_position", m_ui->qcbShowTrackPosition->isChecked());
    settings.setValue("htmlplaylist_plugin/show_track_duration", m_ui->qcbShowTrackDuration->isChecked());

    QDialog::accept();
}
