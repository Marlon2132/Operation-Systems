#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QJsonObject>
#include "apiclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(ApiClient *api, QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void refreshTasks();
    void onCreate();
    void onSave();
    void onDelete();
    void onMarkDone();
    void onItemSelected();

private:
    void loadTasks(const QByteArray &data);

    Ui::MainWindow *ui;
    ApiClient *m_api;
};
