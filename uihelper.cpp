#include "uihelper.h"
#include <QMessageBox>

UiHelper::UiHelper()
{

}

void UiHelper::showMessage(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}
