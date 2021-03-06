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
#include "templatewinamp.h"

#include "template.h"

TemplateBase* Template::templateFor(AvailableTemplates tpl)
{
    switch (tpl)
    {
    case UnstyledHTML:
        return new TemplateUnstyledHTML();
    case Winamp:
        // fallthrough -- winamp is default
    default:
        return new TemplateWinamp();
    }
}

void Template::free(TemplateBase* obj, AvailableTemplates tpl)
{
    switch (tpl)
    {
    case UnstyledHTML:
        delete reinterpret_cast<TemplateUnstyledHTML*>(obj);
        return;
    case Winamp:
        // fallthrough -- winamp is default
    default:
        delete reinterpret_cast<TemplateWinamp*>(obj);
    }
}
