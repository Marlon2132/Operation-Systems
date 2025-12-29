#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

MainWindow::MainWindow(ApiClient *api, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_api(api)
{
    ui->setupUi(this);

    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::refreshTasks);
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreate);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDelete);
    connect(ui->doneButton, &QPushButton::clicked, this, &MainWindow::onMarkDone);
    connect(ui->tasksList, &QListWidget::itemSelectionChanged, this, &MainWindow::onItemSelected);

    refreshTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTasks()
{
    if (!m_api) return;
    m_api->getTasks([this](QByteArray data,int code){
        if (code == 200) {
            loadTasks(data);
        } else {
            QMessageBox::warning(this, "Ошибка", QString("HTTP %1").arg(code));
        }
    });
}

void MainWindow::loadTasks(const QByteArray &data)
{
    ui->tasksList->clear();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isArray()) return;
    for (const QJsonValue &v : doc.array()) {
        if (!v.isObject()) continue;
        QJsonObject o = v.toObject();
        int id = o["id"].toInt();
        QString title = o["title"].toString();
        QString status = o["status"].toString();
        QListWidgetItem *it = new QListWidgetItem(QString("[%1] %2").arg(status, title));
        it->setData(Qt::UserRole, id);
        it->setData(Qt::UserRole + 1, QJsonDocument(o).toJson());
        ui->tasksList->addItem(it);
    }
}

void MainWindow::onCreate()
{
    if (!m_api) return;
    QJsonObject obj;
    obj["title"] = ui->titleLineEdit->text();
    obj["description"] = ui->descriptionTextEdit->toPlainText();
    obj["status"] = ui->statusComboBox->currentText();
    m_api->createTask(obj, [this](QByteArray, int code){
        if (code == 201) refreshTasks();
        else QMessageBox::warning(this, "Ошибка", QString("HTTP %1").arg(code));
    });
}

void MainWindow::onSave()
{
    if (!m_api) return;
    QListWidgetItem *it = ui->tasksList->currentItem();
    if (!it) return;
    int id = it->data(Qt::UserRole).toInt();
    QJsonObject obj;
    obj["title"] = ui->titleLineEdit->text();
    obj["description"] = ui->descriptionTextEdit->toPlainText();
    obj["status"] = ui->statusComboBox->currentText();
    m_api->putTask(id, obj, [this](QByteArray, int code){
        if (code >= 200 && code < 300) refreshTasks();
        else QMessageBox::warning(this, "Ошибка", QString("HTTP %1").arg(code));
    });
}

void MainWindow::onDelete()
{
    if (!m_api) return;
    QListWidgetItem *it = ui->tasksList->currentItem();
    if (!it) return;
    int id = it->data(Qt::UserRole).toInt();

    if (QMessageBox::question(this, "Подтвердите", "Удалить задачу?") != QMessageBox::Yes) return;
    m_api->deleteTask(id, [this](QByteArray, int code){
        if (code == 200) refreshTasks();
        else QMessageBox::warning(this, "Ошибка", QString("HTTP %1").arg(code));
    });
}

void MainWindow::onMarkDone()
{
    if (!m_api) return;
    QListWidgetItem *it = ui->tasksList->currentItem();
    if (!it) return;
    int id = it->data(Qt::UserRole).toInt();
    QJsonObject patch; patch["status"] = "done";
    m_api->patchTask(id, patch, [this](QByteArray, int code){
        if (code >= 200 && code < 300) refreshTasks();
        else QMessageBox::warning(this, "Ошибка", QString("HTTP %1").arg(code));
    });
}

void MainWindow::onItemSelected()
{
    QListWidgetItem *it = ui->tasksList->currentItem();
    if (!it) return;
    QByteArray raw = it->data(Qt::UserRole + 1).toByteArray();
    QJsonDocument doc = QJsonDocument::fromJson(raw);
    if (!doc.isObject()) return;
    QJsonObject o = doc.object();
    ui->titleLineEdit->setText(o["title"].toString());
    ui->descriptionTextEdit->setPlainText(o["description"].toString());
    int idx = ui->statusComboBox->findText(o["status"].toString());
    if (idx >= 0) ui->statusComboBox->setCurrentIndex(idx);
}
