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

#include "templatebase.h"

class TemplateWinamp : public TemplateBase
{
public:
    QString headerStart() const override;
    QString headerEnd() const override;
    QString playlistStatsStart(int numberOfTracks, QString& averageTrackLength) const override;
    QString playlistStatsTotalNumberSingleUnit(int count, QString& unit) const override;
    QString playlistStatsRightClickToSave(QString& url) const override;
    QString playlistStatsEnd() const override;
    QString playlistFilesStart() const override;
    QString playlistFilesEntry(QString& entry) const override;
    QString playlistFilesEnd() const override;
    QString footer() const override;
};
