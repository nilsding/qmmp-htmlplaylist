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

#include "templatewinamp.h"

// use `qmake-qt5 "DEFINES += TEMPLATE_WINAMP_ORIGINAL" ..` to use the original
// Winamp 2 stylesheet -- it seems to display nicely in IE6 only due to its CSS
// parser being a weird mess

QString TemplateWinamp::headerStart() const
{
    return "<html>"
           "<head>"
           "<link rel=\"stylesheet\" href=\"null\">"
           "<style TYPE=\"text/css\">"
           "<!--"
           "BODY { background: #000040; }\n"
           ".para1 { margin-top: -42px; margin-left: 145px; margin-right: 10px; "
#ifdef TEMPLATE_WINAMP_ORIGINAL
           "font-family: \"font2, Arial\"; "
#else
           "font-family: \"Arial\", sans-serif; "
#endif
           "font-size: 30px; line-height: 35px; text-align: left; color: #E1E1E1; }\n"
           ".para2 { margin-top: 15px; margin-left: 15px; margin-right: 50px; "
#ifdef TEMPLATE_WINAMP_ORIGINAL
           "font-family: \"font1, Arial Black\"; "
#else
           "font-family: \"Arial Black\", sans-serif; "
#endif
           "font-size: 50px; line-height: 40px; text-align: left; color: #004080; }\n"
           "-->"
           "</style>"
           "<title>";
}

QString TemplateWinamp::headerEnd() const
{
    return "</title>"
           "</head>"
           "<body BGCOLOR=\"#000080\" topmargin=\"0\" leftmargin=\"0\" text=\"#FFFFFF\">"
           "<!--TOOLBAR_START--><!--TOOLBAR_EXEMPT-->\n"
           "<div align=\"center\">"
           "<div CLASS=\"para2\" align=\"center\"><p>WINAMP</p></div>"
           "<div CLASS=\"para1\" align=\"center\">\n<p>playlist</p></div>"
           "</div>"
           "<hr align=\"left\" width=\"90%\" noshade size=\"1\" color=\"#FFBF00\">"
           "<div align=\"right\">\n"
           "<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"98%\">"
           "<tr>"
           "<td>";
}

QString TemplateWinamp::playlistStatsStart(int numberOfTracks, QString& averageTrackLength) const
{
    return QString("<small>"
                   "<small>"
                   "<font face=\"Arial\" color=\"#FFBF00\">\n")
        .append(QString::number(numberOfTracks))
        .append("</font>"
                "<font color=\"#409FFF\" face=\"Arial\"> tracks in playlist, average track length: </font>"
                "<font face=\"Arial\" color=\"#FFBF00\">")
        .append(averageTrackLength)
        .append("</font>"
                "</small>"
                "</small>"
                "<br>"
                "<small>"
                "<small>"
                "<font color=\"#409FFF\" face=\"Arial\">Playlist length: </font>");
}

QString TemplateWinamp::playlistStatsTotalNumberSingleUnit(int count, QString& unit) const
{
    return QString("<font face=\"Arial\" color=\"#FFBF00\">")
        .append(QString::number(count))
        .append("</font>"
                "<font color=\"#409FFF\" face=\"Arial\"> ")
        .append(unit)
        .append(" </font>");
}

QString TemplateWinamp::playlistStatsRightClickToSave(QString& url) const
{
    return QString("<BR>\n"
                   "<font color=\"#409FFF\" face=\"Arial\">Right-click <a href=\"")
        .append(url)
        .append("\">here</a> to save this HTML file.</font>");
}

QString TemplateWinamp::playlistStatsEnd() const
{
    return "</small>"
           "</small>"
           "</td>"
           "</tr>"
           "</table>"
           "</div>";
}

QString TemplateWinamp::playlistFilesStart() const
{
    return "<blockquote>"
           "<p>"
           "<font color=\"#FFBF00\" face=\"Arial\">"
           "<big>Playlist files:</big>"
           "</font>"
           "<ul>"
           "<font face=\"Arial\" color=\"#FFFFFF\">"
           "<small>"; // yes, that <small> is left open in the Winamp 2.7 output, too :-)
}

QString TemplateWinamp::playlistFilesEntry(QString& entry) const
{
    return QString(entry).append("<BR>\n");
}

QString TemplateWinamp::playlistFilesEnd() const
{
    return "</font>"
           "</ul>"
           "</blockquote>";
}

QString TemplateWinamp::footer() const
{
    return "<hr align=\"left\" width=\"90%\" noshade size=\"1\" color=\"#FFBF00\">"
           "</body>"
           "</html>";
}
