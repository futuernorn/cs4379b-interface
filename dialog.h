  #ifndef DIALOG_H
 #define DIALOG_H

 #include <QDialog>
 #include <QRadioButton>
 #include <QSlider>
#include <QDial>
 #include <QProgressBar>
#include <QLCDNumber>
#include <QComboBox>
#include <QList>
#include <QTabBar>
#include <QPushButton>
 class QAction;
 class QDialogButtonBox;
 class QGroupBox;
 class QLabel;
 class QLineEdit;
 class QMenu;
 class QMenuBar;
 class QPushButton;
 class QTextEdit;

#include <QString>
 class Dialog : public QDialog
 {
     Q_OBJECT

 public:
     Dialog();
  private slots:
  //  void UpdateMethodLineEdit();
 private:
     void createMenu();
     void createMethodGroupBox();
     void createImageSizeGroupBox();
     void createImageBrightnessGroupBox();
  void createColorGroupBox();
     void createLandscapeGroupBox();
    void setMethodEdit(int id);

     enum { NumGridRows = 3, NUM_BUTTONS = 6 };
     
     QMenuBar *menuBar;
     QRadioButton *methodButtons[NUM_BUTTONS];
     QGroupBox *methodGroupBox;
     QGroupBox *imageSizeGroupBox;
     QGroupBox *imageBrightnessGroupBox;
     QGroupBox *colorGroupBox;
     QGroupBox *landscapeGroupBox;
  QLineEdit *methodEdit;

  QComboBox *colorRepComboBox;     
  QTabBar *colorRepTabBar;
     QDialogButtonBox *buttonBox;

     QMenu *fileMenu;
     QAction *exitAction;
 };

 #endif
