// Jeffrey Hogan - CS4379B - Spring 2015
// General layout of code and examples copied from QT documentation at:
// http://qt-project.org/doc/qt-4.8/layouts-basiclayouts.html
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QListWidget;
class QMenu;
class QTextEdit;
class QGroupBox;
class QDial;
class QLCDNumber;
class QLineEdit;
class QRadioButton;
class QVBoxLayout;
class QSlider;
class QProgressBar;
class QComboBox;
class QPushButton;
class QCheckBox;

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow();

  private slots:
     
    void newFile();
    void open();
    void save();
    void help();
        
    void UpdateMethodLineEdit();
    void UpdateBrightnessBar();
    void UpdateColorTabBar();
    void UpdatePortraitCheckbox();
    void UpdateLandscapeCheckbox();

 private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void createDockWindows();

    QTextEdit *textEdit;
     
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
     
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *helpAct;
    QAction *quitAct;

    void createImageSettingsGroupBox();
    void createVisualSettingsGroupBox();
    enum { NumGridRows = 3, NUM_BUTTONS = 6 };

    QList<QString> methodLabels;
    QList<QString> colorRepOptions;
        
    QVBoxLayout *imageSettingsLayout;
    QVBoxLayout *visualSettingsLayout;
    QGroupBox *methodGroupBox;  
    QRadioButton *methodButtons[NUM_BUTTONS];    
    QLineEdit *methodEdit;

    QGroupBox *imageSizeGroupBox;
    QDial *sizeDial;
    QLCDNumber *imageSizeLCD;

    QGroupBox *imageBrightnessGroupBox;
    QSlider *brightnessSlider;
    QProgressBar *brightnessProgressBar;
    
    QGroupBox *colorGroupBox;
    QComboBox *colorRepComboBox;     
    QTabBar *colorRepTabBar;
    
    QGroupBox *landscapeGroupBox;    
    QPushButton *portraitBtn;
    QPushButton *landscapeBtn;
    QCheckBox *portraitCheckBox;
    QCheckBox *landscapeCheckBox;

};

#endif
