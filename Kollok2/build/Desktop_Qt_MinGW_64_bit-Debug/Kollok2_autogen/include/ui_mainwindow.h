/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftLayout;
    QLabel *labelTasks;
    QListWidget *tasksList;
    QPushButton *refreshButton;
    QVBoxLayout *rightLayout;
    QLabel *labelTitle;
    QLineEdit *titleLineEdit;
    QLabel *labelDescription;
    QTextEdit *descriptionTextEdit;
    QLabel *labelStatus;
    QComboBox *statusComboBox;
    QHBoxLayout *buttonsLayout;
    QPushButton *createButton;
    QPushButton *saveButton;
    QPushButton *deleteButton;
    QPushButton *doneButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        leftLayout = new QVBoxLayout();
        leftLayout->setObjectName("leftLayout");
        labelTasks = new QLabel(centralwidget);
        labelTasks->setObjectName("labelTasks");

        leftLayout->addWidget(labelTasks);

        tasksList = new QListWidget(centralwidget);
        tasksList->setObjectName("tasksList");

        leftLayout->addWidget(tasksList);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");

        leftLayout->addWidget(refreshButton);


        horizontalLayout->addLayout(leftLayout);

        rightLayout = new QVBoxLayout();
        rightLayout->setObjectName("rightLayout");
        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName("labelTitle");

        rightLayout->addWidget(labelTitle);

        titleLineEdit = new QLineEdit(centralwidget);
        titleLineEdit->setObjectName("titleLineEdit");

        rightLayout->addWidget(titleLineEdit);

        labelDescription = new QLabel(centralwidget);
        labelDescription->setObjectName("labelDescription");

        rightLayout->addWidget(labelDescription);

        descriptionTextEdit = new QTextEdit(centralwidget);
        descriptionTextEdit->setObjectName("descriptionTextEdit");

        rightLayout->addWidget(descriptionTextEdit);

        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName("labelStatus");

        rightLayout->addWidget(labelStatus);

        statusComboBox = new QComboBox(centralwidget);
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->addItem(QString());
        statusComboBox->setObjectName("statusComboBox");

        rightLayout->addWidget(statusComboBox);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        createButton = new QPushButton(centralwidget);
        createButton->setObjectName("createButton");

        buttonsLayout->addWidget(createButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        buttonsLayout->addWidget(saveButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");

        buttonsLayout->addWidget(deleteButton);

        doneButton = new QPushButton(centralwidget);
        doneButton->setObjectName("doneButton");

        buttonsLayout->addWidget(doneButton);


        rightLayout->addLayout(buttonsLayout);


        horizontalLayout->addLayout(rightLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ToDo OOP Client", nullptr));
        labelTasks->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\207\320\270", nullptr));
        refreshButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272", nullptr));
        labelDescription->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        labelStatus->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        statusComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "todo", nullptr));
        statusComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "in_progress", nullptr));
        statusComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "done", nullptr));

        createButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        doneButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\321\202\320\270\321\202\321\214 done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
