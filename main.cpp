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
        QMdiArea *mdiArea = new QMdiArea(this);
        setCentralWidget(mdiArea);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setTabsClosable(true);
        mdiArea->setTabPosition(QTabWidget::South);
        mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, true);
        mdiArea->setActivationOrder(QMdiArea::ActivationHistoryOrder);

        resize(800, 600);
        setWindowTitle("MDI Application " QT_VERSION_STR);

        createNewWindow(mdiArea);
        createNewWindow(mdiArea);
    }

private slots:
    void createNewWindow(QMdiArea *mdiArea)
    {
        QMdiSubWindow *subWindow = new QMdiSubWindow;
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->setWindowTitle("NEW");
        mdiArea->addSubWindow(subWindow);
        subWindow->show();
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    app.setStyleSheet(QString("QTabBar::tab:bottom:selected { border-bottom: 1px solid; }"));
    return app.exec();
}
