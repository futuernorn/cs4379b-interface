 #include <QtGui>

 #include "dialog.h"

 Dialog::Dialog()
 {
   methodLabels << "A" <<  "B" << "C" << "D" << "E" << "F";
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
      if (methodButtons[i]->isChecked()) {
        //QString value = i;
        methodEdit->setText(methodLabels[i]);
      }
    }
  }

  void Dialog::UpdateSizeLCD()
  {
    //imageSizeLCD->display()
  }

 void Dialog::createMethodGroupBox()
 {
   
   
   
   methodGroupBox = new QGroupBox(tr("Visualization Method"));
     
     
     QVBoxLayout *layout = new QVBoxLayout;
     QHBoxLayout *buttonLayout = new QHBoxLayout;
     QFormLayout *formLayout = new QFormLayout;
     methodEdit = new QLineEdit;
      methodEdit->setText(methodLabels[0]);
     formLayout->addRow(new QLabel(tr("Current Method:")), methodEdit);
    
     QString label;
     for (int i = 0; i < NUM_BUTTONS; ++i) {
       label = "Method &";
       methodButtons[i] = new QRadioButton(label.append(methodLabels[i]), this);
      connect(methodButtons[i],SIGNAL(clicked()),this,SLOT(UpdateMethodLineEdit()));
         buttonLayout->addWidget(methodButtons[i]);
     }
    methodButtons[0]->setChecked(true);
     
     layout->addLayout(buttonLayout);
     layout->addLayout(formLayout);
     
     methodGroupBox->setLayout(layout);
 }

void Dialog::createImageSizeGroupBox()
{
  imageSizeGroupBox = new QGroupBox(tr("Image Size"));
  QFormLayout *layout = new QFormLayout;

  sizeDial = new QDial;  
  imageSizeLCD = new QLCDNumber;
  connect(sizeDial,SIGNAL(valueChanged(int)),imageSizeLCD,SLOT(display(int)));

  sizeDial->setMinimum(50);
  sizeDial->setMaximum(100);
  imageSizeLCD->setPalette(Qt::red);
  layout->addRow(new QLabel(tr("Image Size:")), sizeDial);
  layout->addRow(new QLabel(tr("Current Setting:")), imageSizeLCD);
  imageSizeGroupBox->setLayout(layout);
}

 void Dialog::createImageBrightnessGroupBox()
 {
     imageBrightnessGroupBox = new QGroupBox(tr("Image Brightness"));
     QFormLayout *layout = new QFormLayout;
     brightnessSlider = new QSlider;
     brightnessProgressBar = new QProgressBar;
    connect(brightnessSlider,SIGNAL(valueChanged(int)),brightnessProgressBar,SLOT(setValue(int)));
     brightnessSlider->setOrientation(Qt::Horizontal);
     brightnessSlider->setTickPosition(QSlider::TicksBothSides);
     brightnessSlider->setTickInterval(10);
     brightnessSlider->setSingleStep(1);
     brightnessSlider->setMinimum(0);
     brightnessSlider->setMaximum(255);
     layout->addRow(new QLabel(tr("Image Brightness:")), brightnessSlider);
     layout->addRow(new QLabel(tr("Current Setting:")), brightnessProgressBar);
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
