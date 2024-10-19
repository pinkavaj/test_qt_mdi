#include <fstream>
#include <iostream>
#include <strstream>

#include <QApplication>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QCloseEvent>
#include <QMenuBar>
#include <QAction>

class MainWindow : public QMainWindow
{
public:
    MainWindow()
    {
        mdiArea = new QMdiArea();
        setCentralWidget(mdiArea);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setTabsClosable(true);
        mdiArea->setTabPosition(QTabWidget::South);
        mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, true);
        mdiArea->setActivationOrder(QMdiArea::ActivationHistoryOrder);
        mdiArea->setTabsMovable(true);

        /*
        connect(d->windowMapper, &QSignalMapper::mappedObject,
            this, [=](QObject* object) {
        onSetActiveSubWindow(qobject_cast<QWidget*>(object));
        });

            connect(d->mdiArea, &QMdiArea::subWindowActivated,
            this, &MainWindow::onWindowActivated);
        */

        QMenu *fileMenu = menuBar()->addMenu("Click here");
        QAction *newAction = fileMenu->addAction("New Window");
        connect(newAction, &QAction::triggered, this, &MainWindow::createNewWindow);

        resize(800, 600);
        setWindowTitle("MDI Application" QT_VERSION_STR);
    }

private slots:
    void createNewWindow()
    {
        QMdiSubWindow *subWindow = new QMdiSubWindow;
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->setWindowTitle("NEW");
        mdiArea->addSubWindow(subWindow);
        subWindow->show();
    }

private:
    QMdiArea *mdiArea;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    std::ifstream file("style.css", std::ios::binary);
    if (!file.is_open()) {
        return 1;
    }
    std::strstream buffer;
    buffer << file.rdbuf();
    app.setStyleSheet(QString::fromStdString(buffer.str()));
    return app.exec();
}
