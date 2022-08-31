#ifndef COLOREDTEXT_H
#define COLOREDTEXT_H

#include <QString>
#include <QColor>

class ColoredText
{
public:
    ColoredText(QString, QColor);
    const QString toHtml() const;
private:
    QString content;
    QColor color;
};

#endif // COLOREDTEXT_H
