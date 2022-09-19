#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSqlTableModel>
#include <QMessageBox>
#include "JSONHandler.h"

#define BASE_URL "http://localhost:3189"
#define DATABASE_FILE "stats.db"

#define SEC_MS	1000
#define MIN_MS	(SEC_MS * 60)
#define HOUR_MS	(MIN_MS * 60)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_saveStatsBtn_clicked();
    void saveResult(QNetworkReply *reply);
    void get();
    void slotTimerAlarm();
    void on_resetTimerBtn_clicked();
    void on_changeHostBtn_clicked();

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
    QTime timeDif(const QTime &t1, const QTime &t2);

private:
    Ui::MainWindow *ui;
    JSONHandler* _handler;
    QTimer *_timer;
    QTimer *_milliSecondsTimer;
    QSqlTableModel *_model;
    QTime _startTime;
    QTime _delay;
};


#endif // MAINWINDOW_H
