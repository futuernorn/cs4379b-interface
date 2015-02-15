#include <QtGui>
#include "dialog.h"

Dialog::Dialog()
{
  // QList of QStrings for option and radio button labels
  methodLabels << "A" <<  "B" << "C" << "D" << "E" << "F";
  colorRepOptions << "R" <<  "T" << "S" << "U";
  
  createMenu();
  
  // Generate our 5 "functionalities" group boxes
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
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);
  
  setWindowTitle(tr("Visualization Control"));
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
  methodGroupBox = new QGroupBox(tr("Visualization Method"));
    
  QVBoxLayout *layout = new QVBoxLayout;
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  QFormLayout *formLayout = new QFormLayout;
  
  // initialize method display widget
  methodEdit = new QLineEdit;
  methodEdit->setText(methodLabels[0]); 
  formLayout->addRow(new QLabel(tr("Current Method:")), methodEdit);
  
  QString label;
  for (int i = 0; i < NUM_BUTTONS; ++i) {
    label = "Method &";
    methodButtons[i] = new QRadioButton(label.append(methodLabels[i]), this);
    // Update the method line edit when a new radio button is selected
    connect(methodButtons[i],SIGNAL(clicked()),this,SLOT(UpdateMethodLineEdit()));
    buttonLayout->addWidget(methodButtons[i]);
  }
  
  // select the first method by default
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
  
  // size dial and size LCD directly connected
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
  
  // Link brightness slider with its progress bar display
  // This was done in a custom function to allow for the numeric brightness value to be displayed
  // alongside the progressbar "precentage"
  connect(brightnessSlider,SIGNAL(valueChanged(int)),this,SLOT(UpdateBrightnessBar()));
  
  // Initialize brightness progress bar display and various widget settings
  UpdateBrightnessBar();  
  brightnessSlider->setOrientation(Qt::Horizontal);
  brightnessSlider->setTickPosition(QSlider::TicksBothSides);
  brightnessSlider->setTickInterval(10);
  brightnessSlider->setSingleStep(1);
  brightnessSlider->setMinimum(0);
  brightnessSlider->setMaximum(255);
  brightnessProgressBar->setMinimum(0);
  brightnessProgressBar->setMaximum(255);
  
  layout->addRow(new QLabel(tr("Image Brightness:")), brightnessSlider);
  layout->addRow(new QLabel(tr("Current Setting:")), brightnessProgressBar);
  imageBrightnessGroupBox->setLayout(layout);
}

void Dialog::createColorGroupBox()
{
  colorGroupBox = new QGroupBox(tr("Color Representation"));
  QFormLayout *layout = new QFormLayout;  
  
  colorRepComboBox = new QComboBox;
  colorRepTabBar = new QTabBar;
  
  // Change the selected tab for our display upon a new combo box option being selected
  connect(colorRepComboBox,SIGNAL(activated(QString)),this,SLOT(UpdateColorTabBar()));
  
  QListIterator<QString> i(colorRepOptions);
  int indexCount = 0;  
  // Loop through possible representation options creating a select option and tab for value
  while (i.hasNext()) {
    QString currentOption = i.next();
    colorRepComboBox->addItem(currentOption);
    colorRepTabBar->addTab(currentOption);
    colorRepTabBar->setTabEnabled(indexCount, false);
    indexCount++;
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
  QHBoxLayout *checkBoxLayout = new QHBoxLayout;
  portraitBtn = new QPushButton("&Portrait", this);
  landscapeBtn = new QPushButton("&Landscape", this);
  portraitCheckBox = new QCheckBox("Portrait");
  landscapeCheckBox = new QCheckBox("Landscape");
  portraitCheckBox->setEnabled(false);
  landscapeCheckBox->setEnabled(false);
  
  // Connect the two landscape/portrait buttons to their own callback functions
  connect(portraitBtn,SIGNAL(clicked()),this,SLOT(UpdatePortraitCheckbox()));
  connect(landscapeBtn,SIGNAL(clicked()),this,SLOT(UpdateLandscapeCheckbox()));
  UpdatePortraitCheckbox();
  buttonLayout->addWidget(portraitBtn);
  buttonLayout->addWidget(landscapeBtn);
  checkBoxLayout->addWidget(portraitCheckBox);
  checkBoxLayout->addWidget(landscapeCheckBox);
  layout->addRow(new QLabel(tr("Image Orientation:")), buttonLayout);
  layout->addRow(new QLabel(tr("Current Setting:")), checkBoxLayout);
  
  landscapeGroupBox->setLayout(layout);
  
}


// Various slot functions:
void Dialog::UpdateMethodLineEdit()
{
  for (int i = 0; i < NUM_BUTTONS; ++i) {
    if (methodButtons[i]->isChecked()) {
      methodEdit->setText(methodLabels[i]);
    }
  }
}

void Dialog::UpdateBrightnessBar()
{
  int brightnessValue = brightnessSlider->value();
  brightnessProgressBar->setValue(brightnessValue);
  brightnessProgressBar->setFormat("%p% ("+QString::number(brightnessValue)+")");
}

void Dialog::UpdateColorTabBar()
{
  colorRepTabBar->setCurrentIndex(colorRepComboBox->currentIndex());
}

void Dialog::UpdatePortraitCheckbox()
{
  portraitCheckBox->setChecked(true);
  landscapeCheckBox->setChecked(false);
}
void Dialog::UpdateLandscapeCheckbox()
{
  portraitCheckBox->setChecked(false);
  landscapeCheckBox->setChecked(true);
}
