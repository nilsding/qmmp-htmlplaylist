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

#include <QMessageBox>

#include "htmlplaylist.h"
#include "settingsdialog.h"

#include "htmlplaylistfactory.h"

GeneralProperties HTMLPlaylistFactory::properties() const
{
    GeneralProperties properties;
    properties.name = tr("HTML playlist generator");
    properties.shortName = "htmlplaylist";
    properties.hasAbout = true;
    properties.hasSettings = true;
    properties.visibilityControl = false;
    return properties;
}

QObject* HTMLPlaylistFactory::create(QObject* parent)
{
    return new HTMLPlaylist(parent);
}

QDialog* HTMLPlaylistFactory::createConfigDialog(QWidget* parent)
{
    return new SettingsDialog(parent);
}

void HTMLPlaylistFactory::showAbout(QWidget* parent)
{
    QMessageBox::about(
        parent, tr("About HTML playlist generator"),
        tr("Qmmp HTML playlist generator plug-in") + "\n" +
            tr("This plug-in exports your playlist as a single HTML file, just like in the good ol' days ;-)") + "\n" +
            tr("Written by: Georg Gadinger <nilsding@nilsding.org>"));
}

QString HTMLPlaylistFactory::translation() const
{
    return QLatin1String(":/htmlplaylist_plugin_");
}
