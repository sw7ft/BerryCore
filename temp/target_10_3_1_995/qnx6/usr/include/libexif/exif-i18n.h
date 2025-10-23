/* i18n.h
 *
 * Copyright © 2001 Lutz Müller <lutz@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA.
 */

#ifndef __I18N_H__
#define __I18N_H__

#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (GETTEXT_PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define ngettext(String1,String2,Count) ((Count)==1?(String1):(String2))
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bind_textdomain_codeset(Domain,Codeset) (Codeset)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif


/*! Convert a string from UTF-8 into one appropriate for the current locale
 *  if gettext doesn't doesn't do the conversion itself.
 *  If given a NULL pointer, returns a pointer to an empty string.
 * \param[in] in the string to convert
 * \returns pointer to converted string, which may be in a static buffer
 */
const char *exif_i18n_convert_utf8_to_locale (const char *);
#define C(s) (exif_i18n_convert_utf8_to_locale(s))


#endif /* __I18N_H__ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
