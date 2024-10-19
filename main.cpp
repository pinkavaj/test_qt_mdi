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

    app.setStyleSheet(QString("QTabBar::tab:bottom:selected { border-bottom: 1px solid; }"));
    return app.exec();
}
