#include "caudio.h"
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>


#include "Client/includes/uiworker.h"
#include "Client/includes/config.h"



int main(int argc, char *argv[])
{
    CAudio audio;
    std::cout << "Audio created!\n";
    getchar();
    return 0;
   /* #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    QGuiApplication app(argc,argv);
    //app.setWindowIcon(QIcon("Client/qml/lock_vox_logo_miniature1.png"));
    UIWorker * ui  = new UIWorker(&app);

    app.exec();*/
}


