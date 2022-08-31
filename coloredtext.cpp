#include "coloredtext.h"

ColoredText::ColoredText(QString _content, QColor _color)
{
    content = _content;
    color = _color;
}

const QString ColoredText::toHtml() const
{
    QString colorRgbStr = color.name(QColor::HexRgb);
    return "<font color=" + colorRgbStr + ">" + content.toHtmlEscaped() + "</font>";
}

