#include "singlethemer.h"

/** Get Stylesheet for Named Item

  Returns the stylesheet for a named item, or an empty string if
  no stylesheet is found in the current theme.

  @param p_name
  The name of the stylesheet to load

  @return
  CSS for the stylesheet, as a QString, or an empty QString if
  no stylesheet found by that name
  */

QString SingleThemer::getStyleSheet(QString p_name) {
       Themer* theme = &Singleton<Themer>::Instance();
       return theme->getThemeCSS(p_name);
}

