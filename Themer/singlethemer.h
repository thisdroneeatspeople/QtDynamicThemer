/*



  Copyright (c) 2011-2013 Dynamic Perception

    QtDynamicThemer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QtDynamicThemer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QtDynamicThemer.  If not, see <http://www.gnu.org/licenses/>.

    */

#ifndef SINGLETHEMER_H
#define SINGLETHEMER_H

#include <QString>
#include "singleton.h"
#include "themer.h"

/** Helper Namespace for Themer Singleton

  This namespace provides two helper functions for using Themer as a singleton. This library is NOT
  thread-safe.

  The primary purpose of this namespace is to allow most read-only objects to get their stylesheets
  with a single function call.  For the case of those objects which must interact directly with the
  Themer object, to configure or read configuration, you should use the Singleton templates to access
  the object instead, e.g.:

  @code
  Themer* theme = &Singleton<Themer>::Instance();
  @endcode

  @author
  C. A. Church
  */

namespace SingleThemer {

    QString getStyleSheet(QString p_name);
}
#endif // SINGLETHEMER_H
