 #include <QtGui>

 #include "dialog.h"

 Dialog::Dialog()
 {
   
     createMenu();
     createMethodGroupBox();
     createImageSizeGroupBox();
     createImageBrightnessGroupBox();
  createColorGroupBox();
     createLandscapeGroupBox();



     buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);

     connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
     connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
     connect(methodGroupBox, SIGNAL(clicked()), this, SLOT(updateMethodSelection());
     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->setMenuBar(menuBar);
     mainLayout->addWidget(methodGroupBox);
     mainLayout->addWidget(imageSizeGroupBox);
     mainLayout->addWidget(imageBrightnessGroupBox);
     mainLayout->addWidget(colorGroupBox);
     mainLayout->addWidget(landscapeGroupBox);
 //    mainLayout->addWidget(bigEditor);
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

  void Dialog::UpdateMethodLineEdit()
  {
    for (int i = 0; i < NUM_BUTTONS; ++i) {
      if (methodButtons[i]->isOn()) {
        QString value = i;
        methodEdit->setText(value);
    }
  }
 void Dialog::createMethodGroupBox()
 {
   char methodLabels[] = {'A', 'B', 'C', 'D', 'E', 'F'};
   
   
   methodGroupBox = new QGroupBox(tr("Visualization Method"));
     
     
     QVBoxLayout *layout = new QVBoxLayout;
     QHBoxLayout *buttonLayout = new QHBoxLayout;
     QFormLayout *formLayout = new QFormLayout;
     methodEdit = new QLineEdit;
     formLayout->addRow(new QLabel(tr("Current Method:")), methodEdit);
    
     QString label;
     for (int i = 0; i < NUM_BUTTONS; ++i) {
       label = "Method &";
       methodButtons[i] = new QRadioButton(label.append(methodLabels[i]), this);
      connect(methodButtons[i],SIGNAL(clicked()),this,SLOT(UpdateMethodLineEdit()));
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

 void Dialog::createColorGroupBox()
 {
     colorGroupBox = new QGroupBox(tr("Color Representation"));
     QFormLayout *layout = new QFormLayout;
  QList<QString> colorRepOptions;
  colorRepOptions << "R" <<  "T" << "S" << "U";

  colorRepComboBox = new QComboBox;
  colorRepTabBar = new QTabBar;
  QListIterator<QString> i(colorRepOptions);
  while (i.hasNext()) {
    QString currentOption = i.next();
      colorRepComboBox->addItem(currentOption);
      colorRepTabBar->addTab(currentOption);
  }
  
  
     
     layout->addRow(new QLabel(tr("Color Representation:")), colorRepComboBox);
     layout->addRow(new QLabel(tr("Current Setting:")), colorRepTabBar);
     colorGroupBox->setLayout(layout);
 }

 void Dialog::createLandscapeGroupBox()
{
  landscapeGroupBox = new QGroupBox(tr("Color Representation"));
  QFormLayout *layout = new QFormLayout;
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  QPushButton *portraitButton = new QPushButton("&Portrait", this);
  QPushButton *landscapeBtn = new QPushButton("&Landscape", this);
  buttonLayout->addWidget(portraitButton);
  buttonLayout->addWidget(landscapeBtn);
  layout->addRow(new QLabel(tr("Image Orientation:")), buttonLayout);
  layout->addRow(new QLabel(tr("Current Setting:")), new QLineEdit);

  landscapeGroupBox->setLayout(layout);

}
