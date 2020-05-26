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

#pragma once

#include <QObject>

#include <qmmp/trackinfo.h>

class TemplateBase
{
public:
    TemplateBase();
    virtual ~TemplateBase();

    virtual QString headerStart() const = 0;
    virtual QString headerEnd() const = 0;
    virtual QString playlistStatsStart(int numberOfTracks, QString& averageTrackLength) const = 0;
    virtual QString playlistStatsTotalNumberSingleUnit(int count, QString& unit) const = 0;
    virtual QString playlistStatsRightClickToSave(QString& url) const = 0;
    virtual QString playlistStatsEnd() const = 0;
    virtual QString playlistFilesStart() const = 0;
    virtual QString playlistFilesEntry(QString& entry) const = 0;
    virtual QString playlistFilesEnd() const = 0;
    virtual QString footer() const = 0;
};
