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

#include <QAction>
#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <QTemporaryFile>
#include <QTime>

#include <qmmpui/mediaplayer.h>
#include <qmmpui/playlisttrack.h>
#include <qmmpui/uihelper.h>

#include "template.h"

#include "htmlplaylist.h"

HTMLPlaylist::HTMLPlaylist(QObject* parent) : QObject(parent)
{
    m_action = new QAction(tr("Generate HTML playlist"), this);
    m_action->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_G);
    UiHelper::instance()->addAction(m_action, UiHelper::PLAYLIST_MENU);
    connect(m_action, &QAction::triggered, this, &HTMLPlaylist::exportPlaylistToHTML);
}

HTMLPlaylist::~HTMLPlaylist()
{
}

void HTMLPlaylist::exportPlaylistToHTML()
{
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
    PlayListManager* pl = MediaPlayer::instance()->playListManager();
    auto selectedPlayList = pl->selectedPlayList();
    int trackCount = selectedPlayList->trackCount();
    QList<PlayListTrack*> tracks;
    quint64 totalTrackLength = 0; //!< in milliseconds
    int invalidTracks = 0;
    for (int i = 0; i < trackCount + invalidTracks; i++)
    {
        auto track = selectedPlayList->track(i);
        if (track == nullptr)
        {
            invalidTracks++;
            continue;
        }
        tracks.append(track);
        totalTrackLength += track->duration();
    }
    quint64 totalTrackLengthDays = totalTrackLength / 86400000; // 1 day in ms
    quint64 totalTrackLengthMsec = totalTrackLength % 86400000; // 1 day in ms
    QTime totalTrackLengthTime = QTime::fromMSecsSinceStartOfDay(totalTrackLengthMsec);
    quint64 totalTrackLengthHours =
        (totalTrackLengthDays * 24) + totalTrackLengthTime.hour(); // days are counted in hours
    quint64 averageTrackLength = totalTrackLength / trackCount;
    quint64 averageTrackLengthDays = averageTrackLength / 86400000; // 1 day in ms
    quint64 averageTrackLengthMsec = averageTrackLength % 86400000; // 1 day in ms
    QTime averageTrackLengthTime = QTime::fromMSecsSinceStartOfDay(averageTrackLengthMsec);
    quint64 averageTrackLengthHours =
        (averageTrackLengthDays * 24) + averageTrackLengthTime.hour(); // days are counted in hours

    QTemporaryFile tempFile(QDir::temp().filePath("playlist_XXXXXX.html"));
    tempFile.setAutoRemove(false);
    if (!tempFile.open())
    {
        QMessageBox::critical(qApp->activeWindow(), tr("Error"), tr("Could not create a temporary file."));
        return;
    }
    QUrl tempFileUrl = QUrl("file://" + tempFile.fileName(), QUrl::TolerantMode);

    QString html = "";

    int theme = settings.value("htmlplaylist_plugin/theme", Template::Winamp).toInt();
    TemplateBase* tpl = Template::templateFor(static_cast<Template::AvailableTemplates>(theme));

    // add header
    html.append(tpl->headerStart());
    // header: add title
    html.append(settings.value("htmlplaylist_plugin/title", "Winamp Generated PlayList").toString());
    // header: add rest of </head> and start body
    html.append(tpl->headerEnd());

    // playlist stats: begin
    QString averageTrackLengthFormatted = "";
    if (averageTrackLengthHours > 0)
    {
        averageTrackLengthFormatted.append(QString::number(averageTrackLengthHours));
        averageTrackLengthFormatted.append(":");
        averageTrackLengthFormatted.append(
            averageTrackLengthTime.toString("mm:ss")); // QTime only counts until 24 hours
    }
    else
    {
        averageTrackLengthFormatted.append(averageTrackLengthTime.toString("m:ss"));
    }
    html.append(tpl->playlistStatsStart(trackCount + 1, averageTrackLengthFormatted));
    // playlist stats: append total track length
    if (totalTrackLengthHours > 0)
    {
        QString hour = tr("hour");
        QString hours = tr("hours");
        html.append(
            tpl->playlistStatsTotalNumberSingleUnit(totalTrackLengthHours, totalTrackLengthHours != 1 ? hours : hour));
    }
    if (totalTrackLengthTime.minute() > 0)
    {
        QString minute = tr("minute");
        QString minutes = tr("minutes");
        html.append(tpl->playlistStatsTotalNumberSingleUnit(totalTrackLengthTime.minute(),
                                                            totalTrackLengthTime.minute() != 1 ? minutes : minute));
    }
    QString second = tr("second");
    QString seconds = tr("seconds");
    html.append(tpl->playlistStatsTotalNumberSingleUnit(totalTrackLengthTime.second(),
                                                        totalTrackLengthTime.second() != 1 ? seconds : second));

    if (settings.value("htmlplaylist_plugin/include_save_as", true).toBool())
    {
        // right click to save
        html.append(tpl->playlistStatsRightClickToSave(tempFileUrl.toString().replace("\"", "\\\"")));
    }
    // playlist stats: end
    html.append(tpl->playlistStatsEnd());

    // playlist files: start
    html.append(tpl->playlistFilesStart());
    // playlist files: add each file

    bool showTrackPosition = settings.value("htmlplaylist_plugin/show_track_position", true).toBool();
    bool showTrackDuration = settings.value("htmlplaylist_plugin/show_track_duration", true).toBool();
    for (int i = 0; i < tracks.size(); i++)
    {
        auto tr = tracks.at(i);
        auto artist = tr->value(Qmmp::ARTIST);
        auto title = tr->value(Qmmp::TITLE);
        auto filename = QFileInfo(tr->path()).fileName();
        QString entry = "";

        if (showTrackPosition)
        {
            entry.append(QString::number(i + 1));
            entry.append(". ");
        }

        if (!artist.isEmpty())
        {
            entry.append(artist);
            entry.append(" - ");
        }

        if (title.isEmpty())
        {
            entry.append(filename);
        }
        else
        {
            entry.append(title);
        }

        if (showTrackDuration && !tr->formattedLength().isEmpty())
        {
            entry.append(" (");
            entry.append(tr->formattedLength());
            entry.append(")");
        }

        html.append(tpl->playlistFilesEntry(entry));
    }
    // playlist files: end
    html.append(tpl->playlistFilesEnd());

    // add footer
    html.append(tpl->footer());

    tempFile.write(html.toUtf8());
    tempFile.close();

    qInfo("Wrote playlist to %s", tempFile.fileName().toUtf8().data());
    QDesktopServices::openUrl(tempFileUrl);

    Template::free(tpl, static_cast<Template::AvailableTemplates>(theme));
}
