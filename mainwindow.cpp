#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _handler = new JSONHandler(BASE_URL, DATABASE_FILE, this);
    QObject::connect(_handler->getManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(saveResult(QNetworkReply*)));

    this->setupModel("sessions_info", QStringList() << "id" << "time" << "feature" << "free" << "busy");
    this->createUI();

    _timer = new QTimer();
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(get()));
    _startTime = QTime().currentTime();
    _delay = QTime(0, 5);
    _timer->start(_delay.minute() * MIN_MS + _delay.second() * SEC_MS + _delay.msec());

    _milliSecondsTimer = new QTimer();
    QObject::connect(_milliSecondsTimer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    _milliSecondsTimer->start(1);

    QFont font("Times", 24, QFont::Bold);
    ui->label->setFont(font);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete _handler;
    delete _timer;
    delete _milliSecondsTimer;
    delete _model;
}


void MainWindow::saveResult(QNetworkReply *reply)
{
    _handler->saveResult(reply);
    _model->select();
}


void MainWindow::get()
{
    _handler->getRequest("/v1.0/lm/dongles/products/features");
    _startTime = QTime().currentTime();
}


void MainWindow::slotTimerAlarm()
{
    QTime timerTime = timeDif(_delay, timeDif(QTime().currentTime(), _startTime));
    ui->label->setText(timerTime.toString("mm:ss:zzz"));
}


void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    _model = new QSqlTableModel(this);
    _model->setTable(tableName);

    for(int i = 0, j = 0; i < _model->columnCount(); i++, j++)
        _model->setHeaderData(i,Qt::Horizontal,headers[j]);

    _model->setSort(0,Qt::AscendingOrder);
}


void MainWindow::createUI()
{
    ui->tableView->setModel(_model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    _model->select();

    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

QTime MainWindow::timeDif(const QTime &t1, const QTime &t2)
{
    int diff = t2.msecsTo(t1);
    return QTime(diff / HOUR_MS,
                (diff % HOUR_MS) / MIN_MS,
                (diff % MIN_MS) / SEC_MS,
                 diff % SEC_MS);
}


void MainWindow::on_pushButton_clicked()
{
    _handler->getRequest("/v1.0/lm/dongles/products/features");
}


void MainWindow::on_pushButton_2_clicked()
{
    _startTime = QTime().currentTime();
    _delay = ui->timeEdit->time();
    _timer->start(_delay.minute() * MIN_MS + _delay.second() * SEC_MS + _delay.msec());
}

