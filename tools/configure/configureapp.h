/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qlist.h>
#include <qbuffer.h>
#include <qtextstream.h>
#include <qdir.h>

QT_BEGIN_NAMESPACE

class Configure
{
public:
    Configure( int& argc, char** argv );
    ~Configure();

    void parseCmdLine();
    void validateArgs();
    bool displayHelp();

    QString defaultTo(const QString &option);
    bool checkAvailability(const QString &part);
    void generateQConfigCpp();
    void buildQmake();
    void autoDetection();
    bool verifyConfiguration();

    void generateOutputVars();
    void generateHeaders();
    void generateCachefile();
    void displayConfig();
    void generateMakefiles();
    void generateConfigfiles();
    void detectArch();
    void generateQConfigPri();
    void generateQDevicePri();
    void prepareConfigTests();
    void showSummary();
    QString firstLicensePath();

    bool showLicense(QString licenseFile);
    void readLicense();

    QString addDefine(QString def);

    enum ProjectType {
        App,
        Lib,
        Subdirs
    };

    ProjectType projectType( const QString& proFileName );
    bool isDone();
    bool isOk();

    int platform() const;
    QString platformName() const;
    QString qpaPlatformName() const;

private:
    bool checkAngleAvailability(QString *errorMessage = 0) const;
    QString checkAvx512Availability();

    int verbose;

    // Our variable dictionaries
    QMap<QString,QString> dictionary;
    QStringList allBuildParts;
    QStringList defaultBuildParts;
    QStringList buildParts;
    QStringList nobuildParts;
    QStringList skipModules;
    QStringList licensedModules;
    QStringList allSqlDrivers;
    QStringList disabledModules;
    QStringList enabledModules;
    QStringList modules;
//    QStringList sqlDrivers;
    QStringList configCmdLine;
    QStringList qmakeConfig;
    QStringList qtConfig;

    QStringList qmakeSql;
    QStringList qmakeSqlPlugins;

    QStringList qmakeStyles;
    QStringList qmakeStylePlugins;

    QStringList qmakeVars;
    QStringList qmakeDefines;
    QStringList qmakeIncludes;
    QStringList qmakeLibs;
    QString opensslLibs;
    QString opensslLibsDebug;
    QString opensslLibsRelease;
    QString opensslPath;
    QString dbusPath;
    QString dbusHostPath;
    QString mysqlPath;
    QString psqlLibs;
    QString zlibLibs;
    QString sybase;
    QString sybaseLibs;

    QString outputLine;

    QTextStream outStream;
    QString sourcePath, buildPath;
    QDir sourceDir, buildDir;

    // Variables for usage output
    int optionIndent;
    int descIndent;
    int outputWidth;

    QString confStrOffsets[2];
    QString confStrings[2];
    int confStringOff;

    void addConfStr(int group, const QString &val);
    QString formatPath(const QString &path);
    QString formatPaths(const QStringList &paths);

    QString locateFile(const QString &fileName) const;
    bool findFile(const QString &fileName) const { return !locateFile(fileName).isEmpty(); }
    static QString findFileInPaths(const QString &fileName, const QStringList &paths);
    void reloadCmdLine(int idx);
    void saveCmdLine();

    void addSysroot(QString *command);
    bool tryCompileProject(const QString &projectPath, const QString &extraOptions = QString(),
                           bool distClean = true);
    bool compilerSupportsFlag(const QString &compilerAndArgs);

    void desc(const char *description, int startingAt = 0, int wrapIndent = 0);
    void desc(const char *option, const char *description, bool skipIndent = false, char fillChar = '.');
    void desc(const char *mark_option, const char *mark, const char *option, const char *description, char fillChar = '.');
    void applySpecSpecifics();

    QString formatConfigPath(const char *var);
};

class FileWriter : public QTextStream
{
public:
    FileWriter(const QString &name);
    bool flush();
private:
    QString m_name;
    QBuffer m_buffer;
};

QT_END_NAMESPACE
