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

#include "templateunstyledhtml.h"

QString TemplateUnstyledHTML::headerStart() const
{
    return "<!doctype html>\n"
           "<html>\n"
           "<head>\n"
           "<meta charset=\"utf-8\">\n"
           "<title>";
}

QString TemplateUnstyledHTML::headerEnd() const
{
    return "</title>\n"
           "</head>\n"
           "<body>\n"
           "<h1>Playlist</h1>\n";
}

QString TemplateUnstyledHTML::playlistStatsStart(int numberOfTracks, QString& averageTrackLength) const
{
    return QString("<div><strong>")
        .append(QString::number(numberOfTracks))
        .append("</strong> tracks in playlist, average track length: <strong>")
        .append(averageTrackLength)
        .append("</strong>"
                "</div>\n"
                "<div>Playlist length: ");
}

QString TemplateUnstyledHTML::playlistStatsTotalNumberSingleUnit(int count, QString& unit) const
{
    return QString("<strong>").append(QString::number(count)).append("</strong> ").append(unit).append(" ");
}

QString TemplateUnstyledHTML::playlistStatsRightClickToSave(QString& url) const
{
    return QString("</div>\n"
                   "<div>Right-click <a href=\"")
        .append(url)
        .append("\">here</a> to save this HTML file.");
}

QString TemplateUnstyledHTML::playlistStatsEnd() const
{
    return "</div>\n";
}

QString TemplateUnstyledHTML::playlistFilesStart() const
{
    return "<h2>Playlist files:</h2>\n"
           "<ul>\n";
}

QString TemplateUnstyledHTML::playlistFilesEntry(QString& entry) const
{
    return QString("  <li>").append(entry).append("\n");
}

QString TemplateUnstyledHTML::playlistFilesEnd() const
{
    return "</ul>";
}

QString TemplateUnstyledHTML::footer() const
{
    return "<hr>\n"
           "<em>Generated with the <a href=\"https://github.com/nilsding/qmmp-htmlplaylist\">qmmp htmlplaylist "
           "plug-in</a>.</em>\n"
           "</body>\n"
           "</html>\n";
}
