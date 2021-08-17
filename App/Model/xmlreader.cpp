#include "xmlreader.h"

XMLReader::XMLReader(QObject *parent) : QObject(parent)
{
}

QString XMLReader::filePath()
{
    return _filePath;
}

void XMLReader::setFilepath(QString path)
{
    _filePath = path;//QUrl(path).toString(QUrl::PreferLocalFile | QUrl::StripTrailingSlash);
    emit filepathChanged(path);
}

