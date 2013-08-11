#include "themer.h"

#include <QDebug>


Themer::Themer(QObject* parent) : QObject(parent) {
        // default theme path
    m_themePath = QCoreApplication::applicationDirPath() + "/themes";
    m_themeList = new QHash<QString, QString>;
    m_curTheme  = "";

    _getThemeList();
}

Themer::~Themer() {
    delete m_themeList;
}

/** Repolish Widget

  Static method to re-polish any given widget and force an update on it.

  @param p_widget
  The widget to re-polish
  */

void Themer::rePolish(QWidget *p_widget) {
    p_widget->style()->unpolish(p_widget);
    p_widget->style()->polish(p_widget);
    p_widget->update();
}

/** Get all Theme Names */
QList<QString> Themer::themes() {

    QList<QString> retList = m_themeList->keys();
    return retList;
}

 /** Get Current Theme Directory */
QString Themer::themePath() {
    return m_themePath;
}

/** Set Current Theme Directory

  Setting the theme directory causes the theme list to be
  immediately refreshed.
  */
void Themer::themePath(QString p_path) {
    m_themePath = p_path;
    _getThemeList();
}

/** Set Theme

  Set the current theme name, from the theme list.

  If the theme name does not exist, this method is
  non-operative.

  */

void Themer::theme(QString p_theme) {
    if( ! m_themeList->contains(p_theme) ) {
        qDebug() << "Themer: No theme found by name" << p_theme;
        return;
    }

    qDebug() << "Themer: Set theme" << p_theme;

    m_curTheme = p_theme;
    emit themeChanged();
}

/** Get Theme

  Gets the currently set theme name
  */

QString Themer::theme() {
    return m_curTheme;
}

/** Get the CSS Associated with an Item

  Returns the CSS contents for a particularly-identified item, if it
  exists.

  @param p_which
  The name of the item to get a theme for.

  @return
  A string containing the CSS for the item, or an empty string if no CSS file
  was found for the item.

  */

QString Themer::getThemeCSS(QString p_which) {

    qDebug() << "Themer: Request for widget CSS" << p_which;

    QString basePath = m_themeList->value(m_curTheme);

    QString cssFile  = basePath + "/" + p_which + ".qss";
    QString retCss;

    retCss = _fileContents(cssFile);

    // look for os-specific files

    QString suffix = _osSuffix();
    QString sufCssFile = basePath + "/" + p_which + suffix + ".qss";

    retCss.append(_fileContents(sufCssFile));

    return retCss;
}



void Themer::_getThemeList() {

    qDebug() << "Themer: Using Theme Directory" << m_themePath;

    m_themeList->clear();

    QDir themeDir(m_themePath);

    themeDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    QStringList dirs = themeDir.entryList();

    qDebug() << dirs;

    foreach(QString dir, dirs) {
        qDebug() << "Themer: Found Directory" << dir;
        QString path = m_themePath + "/" + dir;
        _loadTheme(path, dir);
    }

        // if only one theme, set current theme to it
    if( m_themeList->count() == 1 )
        m_curTheme = m_themeList->keys().at(0);
}


void Themer::_loadTheme(QString p_path, QString p_dirname) {

    QString name;
    QString themeDesc = p_path + "/" + "theme.ini";
    QFile descFile(themeDesc);


    if( ! descFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
            // no ini file found, or is not readable
        qDebug() << "Themer: No INI file found, using directory as name";
        name = p_dirname;
    }
    else {
            // ini file exists
        QTextStream in(&descFile);

        while( ! in.atEnd() ) {
            QString curLine = in.readLine();
            QStringList keyval = curLine.split("=");

            if( keyval.at(0) == "name" && keyval.count() > 1)
                name = keyval.at(1);
        }

        descFile.close();
    }


    if( name.length() > 0 )
        m_themeList->insert(name, p_path);
}

QString Themer::_osSuffix() {
#if QT_VERSION < 0x050000
        // Qt 4.x
    #ifdef Q_WS_X11
        return QString("_linux");
    #endif

    #ifdef Q_WS_MAC
        return QString("_osx");
    #endif

    #ifdef Q_WS_QWS
        return QString("_elinux");
    #endif

    #ifdef Q_WS_WIN
        return QString("_win");
    #endif
#else
        // Qt 5.x
    #ifdef Q_OS_LINUX
        return QString("_linux");
    #endif

    #ifdef Q_OS_MAC
        return QString("_osx");
    #endif

    #ifdef Q_OS_WIN
        return QString("_win");
    #endif
#endif
}


QString Themer::_fileContents(QString p_path) {
    QFile contents(p_path);
    QString ret;

    if( ! QFile::exists(p_path) )
        return ret;

    if( ! contents.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug() << "Themer: Could not open file: " << p_path;
        return QString();
    }

    QTextStream in(&contents);

    while( ! in.atEnd() )
        ret.append(in.readLine());

    contents.close();


        // convert relative paths in theme files to absolute paths
    ret.replace("url(", "url(" + QCoreApplication::applicationDirPath() + "/");


    return ret;
}
