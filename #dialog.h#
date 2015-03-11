// Jeffrey Hogan - CS4379B - Spring 2015
// General layout of code and examples copied from QT documentation at:
// http://qt-project.org/doc/qt-4.8/layouts-basiclayouts.html
#ifndef DIALOG_H
  #define DIALOG_H
  
  #include <QDialog>
  #include <QList>
  #include <QString>
  class QRadioButton;
  class QSlider;
  class QDial;
  class QProgressBar;
  class QLCDNumber;
  class QComboBox;
  class QTabBar;
  class QCheckBox;
  class QAction;
  class QDialogButtonBox;
  class QGroupBox;
  class QLabel;
  class QLineEdit;
  class QMenu;
  class QMenuBar;
  class QPushButton;
  class QTextEdit;

  class Dialog : public QDialog
  {
    Q_OBJECT
    
    public:
    Dialog();
    private slots:
    void UpdateMethodLineEdit();
    void UpdateBrightnessBar();
    void UpdateColorTabBar();
    void UpdatePortraitCheckbox();
    void UpdateLandscapeCheckbox();
    private:
    void createMenu();
    void createMethodGroupBox();
    void createImageSizeGroupBox();
    void createImageBrightnessGroupBox();
    void createColorGroupBox();
    void createLandscapeGroupBox();
    void setMethodEdit(int id);
    
    enum { NumGridRows = 3, NUM_BUTTONS = 6 };
    
    QList<QString> methodLabels;
    QList<QString> colorRepOptions;
        
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

    QMenuBar *menuBar;
    QDialogButtonBox *buttonBox;    
    QMenu *fileMenu;
    QAction *exitAction;
  };
  
#endif
