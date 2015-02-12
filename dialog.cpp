 #include <QtGui>

 #include "dialog.h"

 Dialog::Dialog()
 {
   
     createMenu();
     createMethodGroupBox();
     createImageSizeGroupBox();
     createImageBrightnessGroupBox();
     createFormGroupBox();

     bigEditor = new QTextEdit;
     bigEditor->setPlainText(tr("This widget takes up all the remaining space "
                                "in the top-level layout."));

     buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);

     connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
     connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->setMenuBar(menuBar);
     mainLayout->addWidget(methodGroupBox);
     mainLayout->addWidget(imageSizeGroupBox);
     mainLayout->addWidget(imageBrightnessGroupBox);
     mainLayout->addWidget(formGroupBox);
     mainLayout->addWidget(bigEditor);
     mainLayout->addWidget(buttonBox);
     setLayout(mainLayout);

     setWindowTitle(tr("Basic Layouts"));
 }

 void Dialog::createMenu()
 {
     menuBar = new QMenuBar;

     fileMenu = new QMenu(tr("&File"), this);
     exitAction = fileMenu->addAction(tr("E&xit"));
     menuBar->addMenu(fileMenu);

     connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
 }

 void Dialog::createMethodGroupBox()
 {
   char methodLabels[] = {'A', 'B', 'C', 'D', 'E', 'F'};
   
   
   methodGroupBox = new QGroupBox(tr("Visualization Method"));
     
     
     QVBoxLayout *layout = new QVBoxLayout;
     QHBoxLayout *buttonLayout = new QHBoxLayout;
     QFormLayout *formLayout = new QFormLayout;
     formLayout->addRow(new QLabel(tr("Current Method:")), new QLineEdit);
    
     QString label;
     for (int i = 0; i < NUM_BUTTONS; ++i) {
       label = "Method &";
       methodButtons[i] = new QRadioButton(label.append(methodLabels[i]), this);
         buttonLayout->addWidget(methodButtons[i]);
     }
     
     layout->addLayout(buttonLayout);
     layout->addLayout(formLayout);
     
     methodGroupBox->setLayout(layout);
 }

void Dialog::createImageSizeGroupBox()
{
  imageSizeGroupBox = new QGroupBox(tr("Image Size"));
  QFormLayout *layout = new QFormLayout;
  QDial *sizeDial = new QDial;
  sizeDial->setMinimum(50);
  sizeDial->setMaximum(100);
  layout->addRow(new QLabel(tr("Image Size:")), sizeDial);
  layout->addRow(new QLabel(tr("Current Setting:")), new QLineEdit);
  imageSizeGroupBox->setLayout(layout);
}

 void Dialog::createImageBrightnessGroupBox()
 {
     imageBrightnessGroupBox = new QGroupBox(tr("Image Brightness"));
     QFormLayout *layout = new QFormLayout;
     QSlider *brightnessSlider = new QSlider;
     brightnessSlider->setOrientation(Qt::Horizontal);
     brightnessSlider->setTickPosition(QSlider::TicksBothSides);
     brightnessSlider->setTickInterval(10);
     brightnessSlider->setSingleStep(1);
     brightnessSlider->setMinimum(0);
     brightnessSlider->setMaximum(255);
     layout->addRow(new QLabel(tr("Image Brightness:")), brightnessSlider);
     layout->addRow(new QLabel(tr("Current Setting:")), new QLineEdit);
     imageBrightnessGroupBox->setLayout(layout);
 }

 void Dialog::createFormGroupBox()
 {
     formGroupBox = new QGroupBox(tr("Form layout"));
     QFormLayout *layout = new QFormLayout;
     layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
     layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
     layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
     formGroupBox->setLayout(layout);
 }
