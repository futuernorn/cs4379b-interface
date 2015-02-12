  #ifndef DIALOG_H
 #define DIALOG_H

 #include <QDialog>
 #include <QRadioButton>
 #include <QSlider>
#include <QDial>
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

 private:
     void createMenu();
     void createMethodGroupBox();
     void createImageSizeGroupBox();
     void createImageBrightnessGroupBox();
     void createFormGroupBox();

     enum { NumGridRows = 3, NUM_BUTTONS = 6 };
     
     QMenuBar *menuBar;
     QRadioButton *methodButtons[NUM_BUTTONS];
     QGroupBox *methodGroupBox;
     QGroupBox *imageSizeGroupBox;
     QGroupBox *imageBrightnessGroupBox;
     QGroupBox *formGroupBox;
     QTextEdit *smallEditor;
     QTextEdit *bigEditor;
     QLabel *labels[NumGridRows];
     QLineEdit *lineEdits[NumGridRows];
     
     QDialogButtonBox *buttonBox;

     QMenu *fileMenu;
     QAction *exitAction;
 };

 #endif
