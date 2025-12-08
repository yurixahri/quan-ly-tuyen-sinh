#ifndef FS_H
#define FS_H


#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <QString>
#include <QCryptographicHash>
#include <QSettings>
#include <QCollator>
#include <QMimeType>
#include <QMimeDatabase>
#include <QStorageInfo>
#include <QFuture>



inline QStringList getMountedVolumes() {
    QStringList list;
    QList<QStorageInfo> volumes = QStorageInfo::mountedVolumes();

    for (const QStorageInfo &storage : std::as_const(volumes)) {
        if (storage.isReady() && !storage.isReadOnly()) {
            list.append(storage.rootPath());
        }
    }
    return list;
}

inline bool isExist(const QString &path){
    QFileInfo info(path);
    return info.exists();
}

inline bool isFile(const QString &path){
    QFileInfo info(path);
    return info.isFile();
}

inline QMimeType getMimeType(const QString &path){
    QFileInfo info(path);
    QMimeDatabase mimeDatabase;
    return mimeDatabase.mimeTypeForFile(info);
}


inline QStringList getDirectories(const QString &path){
    QDir dir(path);

    QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QCollator collator;
    collator.setNumericMode(true);
    collator.setCaseSensitivity(Qt::CaseInsensitive);
    std::sort(list.begin(), list.end(), [&](const QString &a, const QString &b) {
        return collator.compare(a, b) < 0;
    });
    return list;
}

inline QStringList getFiles(const QString &path){
    QDir dir(path);

    QStringList list = dir.entryList(QDir::Files);
    QCollator collator;
    collator.setNumericMode(true);
    collator.setCaseSensitivity(Qt::CaseInsensitive);
    std::sort(list.begin(), list.end(), [&](const QString &a, const QString &b) {
        return collator.compare(a, b) < 0;
    });
    return list;
}

inline QString getExt(QString &string){
    QString ext = string.split(".").back();
    return ext;
}

inline bool removeFile(QString path){
    return QFile::remove(path);
}

inline bool removeDirectory(QString path){
    QDir dir(path);
    return dir.removeRecursively();
}

inline bool makeDirectory(QString path){
    QDir dir;
    if (!dir.exists(path)) {
        if (dir.mkpath(path)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

#endif // FS_H
